# MD5

## Context

MD5 (Message-Digest Algorithm 5) was designed by Ronald Rivest in 1991 as a replacement
for MD4, whose design was suspected — and later confirmed — to be weak. It was formally
specified in 1992 as [RFC 1321](https://www.rfc-editor.org/rfc/rfc1321), and produces a
128-bit (16-byte) digest.

MD5 was historically used for a wide range of security purposes: digital signatures, TLS
certificates, password storage, and file integrity checks. Its security has since collapsed:
the first weaknesses in its internal compression function appeared as early as 1996, and
practical collision attacks (two different inputs producing the same digest) were
demonstrated in 2004. Since then, MD5 has been considered cryptographically broken and is
no longer suitable for any security-sensitive purpose.

Despite this, MD5 is still widely encountered today — mainly for **non-cryptographic**
uses such as checksums to detect accidental file corruption, or as a fast hash for
non-adversarial contexts (e.g. partitioning keys in a database). This is also what makes
it a good learning exercise: it's simple enough to fully understand and implement by hand,
while still covering all the core ideas found in more modern hash functions like SHA-256.

## How it works

MD5 processes a message of arbitrary length and produces a fixed 128-bit digest. It
belongs to the Merkle–Damgård family of hash constructions: the message is split into
fixed-size blocks, and a running state is updated block by block until the whole message
has been consumed.

### 1. Padding

Before processing, the message is padded so that its length becomes a multiple of 512
bits (64 bytes):
- A single `1` bit (the byte `0x80`) is appended right after the message.
- Zero bits are appended until the length reaches 448 bits (56 bytes) within the current
  block. If there isn't enough room left in the current block for this (i.e. the message
  already crossed the 56-byte mark once `0x80` is added), the current block is padded with
  zeros and processed, and a brand new all-zero block is started instead.
- The last 8 bytes of the final block are filled with the original message length,
  expressed in bits, encoded in little-endian.

The purpose of padding is purely structural: it guarantees the message can be split
cleanly into complete 64-byte blocks, which the rest of the algorithm requires. Encoding
the original length is what prevents trivial length-extension ambiguities between
messages of different sizes that happen to pad to the same content.

### 2. State initialization

MD5 keeps a running state made of four 32-bit registers (`A`, `B`, `C`, `D`), set to fixed
starting values defined by the specification:

```
A = 0x67452301
B = 0xefcdab89
C = 0x98badcfe
D = 0x10325476
```

These are arbitrary but fixed constants — there's no deeper meaning to derive from them,
they simply need to match the spec exactly.

### 3. Per-block processing (the compression function)

Each 64-byte block is processed independently, updating `A`, `B`, `C`, `D` through **64
rounds**, split into 4 groups of 16 rounds. Each group uses a different non-linear mixing
function:

| Rounds | Function | Formula |
|--------|----------|---------|
| 0–15   | F        | `(B & C) \| (~B & D)` |
| 16–31  | G        | `(D & B) \| (~D & C)` |
| 32–47  | H        | `B ^ C ^ D` |
| 48–63  | I        | `C ^ (B \| ~D)` |

At each round, the block's 16 32-bit words (`M[0..15]`, extracted from the 64 bytes in
little-endian) are combined with the current state, a precomputed constant `K[i]`, and a
left rotation by a fixed amount `S[i]`. Which word of `M[]` is used at each round follows
a different formula per group — it is **not** simply `i % 16`.

The role of this stage is to thoroughly mix the input bits with the running state, in a
way that's fast to compute but hard to invert or predict.

### 4. Finalization

Once all blocks have been processed, the final digest is the concatenation of `A`, `B`,
`C`, `D` in little-endian — 16 bytes, usually displayed as 32 hexadecimal characters.

## Implementation notes and pitfalls

- **Streaming design (`init` / `update` / `final`)**: rather than padding the entire
  message upfront, the implementation keeps a running 64-byte buffer and processes a block
  as soon as it's full. This avoids loading an entire file into memory and mirrors how
  real-world implementations (OpenSSL, `md5sum`) work internally.

- **Endianness**: MD5 is defined entirely in **little-endian** — both when extracting the
  16 words from a block, and when encoding the final length field. Getting this backwards
  produces a digest that compiles and runs fine but is silently wrong, with no way to
  detect the mistake except by testing against known vectors.

- **The padding threshold**: the boundary check (whether there's still room for the length
  field within the current block) is an easy off-by-one target. It has to account for the
  extra `0x80` byte, and be tested explicitly against messages of exactly 55, 56, 63, and
  64 bytes — each one exercises a different edge of this boundary.

- **Per-block state vs. running state**: the four registers must be saved *before* the 64
  rounds of a block begin, and added back into the running state only *after* all 64
  rounds complete — using the pre-round values, not the values from the last round. Mixing
  this up produces plausible-looking but incorrect digests.

- **Unsigned overflow**: additions inside the compression function are expected to wrap
  around modulo 2³². Using `uint32_t` throughout makes this automatic and well-defined in
  C — using a signed type here would be undefined behavior on overflow.

- **The `K[]` and `S[]` tables**: both must contain exactly 64 entries. A missing or
  duplicated value silently shifts every following round's constant, again producing a
  wrong-but-plausible digest rather than a crash.

- **Validating correctness**: because incorrect implementations rarely crash or produce
  obviously wrong output, testing against official test vectors is essential rather than
  optional — e.g. `md5("") = d41d8cd98f00b204e9800998ecf8427e` and
  `md5("abc") = 900150983cd24fb0d6963f7d28e17f72`.

## Resources

- [RFC 1321 — The MD5 Message-Digest Algorithm](https://www.rfc-editor.org/rfc/rfc1321)
