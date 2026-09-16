# Whirlpool

## Context

Whirlpool was designed by Vincent Rijmen (co-creator of AES) and Paulo S. L. M. Barreto,
and first described in 2000. It was submitted to the NESSIE project (a European effort to
identify strong cryptographic primitives) and was recommended by it; it later became part
of the joint ISO/IEC 10118-3 international standard for dedicated hash functions. It
produces a 512-bit (64-byte) digest.

Unlike MD5 or SHA-256, Whirlpool is not a purpose-built hash function from the ground up —
it is built around an internal 512-bit block cipher with a structure closely derived from
AES, turned into a hash function through the Miyaguchi-Preneel construction. No practical
collision or preimage attack is known against it to date. It is less widely deployed than
the SHA-2 family, but it appears in some real-world applications — for instance as one of
the hash options in disk-encryption tools such as VeraCrypt — and is a good subject to
study because its AES-like internals make it a natural next step after implementing AES
or a Merkle–Damgård hash like MD5/SHA-256.

## How it works

Whirlpool follows the same overall shape as MD5/SHA-256 (pad the message, split it into
blocks, process each block through a compression step that updates a running state), but
its compression step is built very differently: instead of a dedicated set of bitwise
rounds, it reuses a full block cipher.

### 1. Padding

The message is padded to a multiple of 512 bits (64 bytes), following the same general
principle as MD5/SHA-256: append a `1` bit (the byte `0x80`), then zero bits, then the
original message length. The one significant difference is the size of the length field:
Whirlpool reserves the **last 32 bytes** (256 bits) of the final block for it, rather than
8 bytes — which also shifts the "does it still fit in this block" threshold from 56 down
to 32 bytes.

### 2. State initialization

The running hash state `H` is a 64-byte (8×8 byte matrix) value, initialized to all
zeros before the first block is processed.

### 3. The internal cipher (per block)

Each 64-byte message block `M` is loaded into an 8×8 byte matrix and encrypted with an
AES-like block cipher, using the current hash state `H` as the encryption key. Each of
its 10 rounds applies four transformations, directly analogous to AES:

| Step | Role |
|------|------|
| SubBytes | Byte-wise substitution through a fixed 256-entry S-Box |
| ShiftColumns | Cyclically shifts each column of the matrix, column `j` shifted by `j` positions |
| MixRows | Diffuses each row through a matrix multiplication in GF(2⁸) |
| AddRoundKey | XORs the state with the current round key |

An initial `AddRoundKey` with the unmodified key `H` is applied before round 1 begins.

### 4. Key schedule

Whirlpool does not use a separate key-schedule algorithm. Instead, each round key is
derived from the previous one by applying the **exact same four transformations**
(SubBytes, ShiftColumns, MixRows) to it, followed by an `AddRoundKey` with a fixed round
constant instead of a data-dependent key. The very first round key is `H` itself. This
means the same round-function code can be reused both to encrypt the block and to
generate the keys that drive that encryption.

### 5. Miyaguchi-Preneel finalization

Once the block cipher has produced a ciphertext `C` for the block `M` under key `H`, the
hash state is updated as:

```
H_new = C XOR M XOR H
```

This is what turns a reversible block cipher into a one-way hash function: even knowing
`H_new`, recovering `M` or `H` is not straightforward, unlike a plain block cipher
encryption which can always be undone with the key.

### 6. Finalization

Once every block (including the padding block) has been processed, `H` — 64 bytes — is
the final digest, usually displayed as 128 hexadecimal characters.

## Implementation notes and pitfalls

- **Streaming design (`init` / `update` / `final`)**: the same buffering pattern used for
  MD5/SHA-256 applies here — a 64-byte buffer accumulates incoming data and is processed
  block by block, keeping memory usage constant regardless of input size.

- **Byte-to-matrix convention must be consistent everywhere**: bytes are mapped onto the
  8×8 state matrix using some indexing convention (e.g. `matrix[i][j] = bytes[8*i + j]`).
  This convention has to be used identically every time bytes are loaded into a matrix
  *and* every time a matrix is flattened back into bytes — including the final
  Miyaguchi-Preneel XOR step that updates `H`. Using one convention in one place and a
  different one elsewhere doesn't crash anything: it silently scrambles which byte ends up
  where, producing a wrong-but-plausible-looking digest.

- **ShiftColumns direction**: the shift amount for column `j` is `j` positions — it's easy
  to get the direction backwards, or to write the modular arithmetic in a way that
  accidentally cancels out to a no-op (shifting a column by 0 positions for every `j`).
  A shift that silently does nothing is particularly easy to miss, since the function
  still runs without error — it just fails to diffuse any information between rows.

- **MixRows matrix orientation**: the diffusion matrix is not symmetric, so
  `state[i][k] × MDS[k][j]` and `state[i][k] × MDS[j][k]` are genuinely different
  operations, even though the matrix is circulant. Since the matrix is still a valid MDS
  matrix either way, swapping the indices doesn't produce an obviously broken result —
  just a digest that doesn't match the standard.

- **The GF(2⁸) reduction polynomial differs from AES's**: Whirlpool uses `0x1D` as its
  reduction constant, whereas AES uses `0x1B`. If MixRows is adapted from an existing
  AES MixColumns implementation, this is an easy constant to carry over by mistake.

- **The key schedule constants are fixed, not derived from the message**: the round
  constants used in `AddRoundKey` during key-schedule steps come from the S-Box applied to
  a fixed sequence of bytes, with only the first row of each round's constant matrix being
  non-zero — the other seven rows are all zero. Getting this structure wrong (e.g. filling
  more than the first row) breaks the key schedule silently.

- **Validating correctness**: as with MD5/SHA-256, a broken implementation rarely crashes
  or produces obviously wrong output, so testing against official vectors is essential —
  e.g. `whirlpool("") = 19fa61d75522a4669b44e39c1d2e1726c530232130d407f89afee0964997f7a73e83be698b288febcf88e3e03c4f0757ea8964e59b63d93708b138cc42a66eb3`
  and
  `whirlpool("abc") = 4e2448a4c6f486bb16b6562c73b4020bf3043e3a731bce721ae1b303d97e6d4c7181eebdb6c57e277d0e34957114cbd6c797fc9d95d8b582d225292076d4eef5`.
  Testing at least one multi-block message is also worthwhile, since a single-block test
  alone won't catch a bug in how blocks are chained together.

## Resources

- Barreto, P. S. L. M., Rijmen, V. — [*The Whirlpool Hashing Function*](https://www.researchgate.net/publication/228610491_The_Whirlpool_hashing_function)
- [ISO/IEC 10118-3:2018 — Dedicated Hash-Function 7 (WHIRLPOOL)](https://www.iso.org/standard/67116.html)
