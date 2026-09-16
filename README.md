# ft_ssl

From-scratch, C reimplementation of core cryptographic building blocks — built as part
of the 42 curriculum. This repository is designed to grow over time: it will eventually
bring together a hashing module, a symmetric encryption module, and an asymmetric
encryption module, each implemented without relying on any existing cryptographic library.

For now, only the **hashing** module is implemented.

## Usage

Build the project:

```bash
make
```

Hash a string directly:

```bash
./ft_ssl md5 -s "hello world"
./ft_ssl sha256 -s "hello world"
./ft_ssl whirlpool -s "hello world"
```

Hash the contents of STDIN:

```bash
echo "hello world" | ./ft_ssl md5
```

Hash a file:

```bash
./ft_ssl md5 my_file.txt
```

Echo STDIN input alongside its hash:

```bash
echo "hello world" | ./ft_ssl sha256 -p
```

Run the tester:

```bash
make test
```

Available flags:

| Flag | Effect |
|------|--------|
| `-p` | Echoes STDIN input in addition to the hash |
| `-q` | Quiet mode (hash only, no source name) |
| `-r` | Reverses the display order (hash before the source) |
| `-s` | Hashes the given string argument directly |

## Implemented algorithms

| Algorithm | Digest size | Detailed documentation |
|-----------|-------------|--------------------------|
| MD5       | 128 bits    | [doc/md5.md](./doc/md5.md) |
| SHA-256   | 256 bits    | [doc/sha256.md](./doc/sha256.md) |
| WHIRLPOOL | 512 bits    | [doc/whirlpool.md](./doc/whirlpool.md) |

Each file in `doc/` details how the algorithm works, the approach taken to implement it,
and the main difficulties encountered along the way.

## Design choices

- **`init` / `update` / `final` pattern**: each hashing algorithm processes data in a
  streaming fashion rather than loading it all into memory at once, which allows hashing
  files of arbitrary size without being limited by available RAM.
- **Polymorphism via function pointers**: a `t_hash_algo` struct groups the `init`/`update`/
  `final` functions of each algorithm, letting all parsing, input-reading (file/string/stdin),
  and output logic be written once and shared between MD5, SHA-256, and Whirlpool.
- **Argument parsing**: flag recognition stops as soon as the first positional argument
  (a filename) is encountered, matching the behavior expected by the subject — a `-s`
  appearing after a filename is then treated as a literal filename rather than an option.

## Resources

- [RFC 1321 — The MD5 Message-Digest Algorithm](https://www.rfc-editor.org/rfc/rfc1321)
- [FIPS 180-4 — Secure Hash Standard (SHA-256 specification)](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)
- [Barreto, P. S. L. M., Rijmen, V. — The Whirlpool Hashing Function](https://www.researchgate.net/publication/228610491_The_Whirlpool_hashing_function)
- [ISO/IEC 10118-3:2018 — Dedicated Hash-Function 7 (WHIRLPOOL)](https://www.iso.org/standard/67116.html)
- [OpenSSL documentation](https://docs.openssl.org/)

## Coming up

- Symmetric encryption
- Asymmetric encryption
