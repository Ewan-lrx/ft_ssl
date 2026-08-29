# ft_ssl

From-scratch, C reimplementation of core cryptographic building blocks — built as part
of the 42 curriculum. This repository is designed to grow over time: it will eventually
bring together a hashing module, a symmetric encryption module, and an asymmetric
encryption module, each implemented without relying on any existing cryptographic library.

For now, only the **hashing** module is implemented.

## Usage

```bash
make

./ft_ssl md5 -s "hello world"
./ft_ssl sha256 -s "hello world"

echo "hello world" | ./ft_ssl md5

./ft_ssl md5 my_file.txt

echo "hello world" | ./ft_ssl sha256 -p
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

Each file in `doc/` details how the algorithm works, the approach taken to implement it,
and the main difficulties encountered along the way.

## Design choices

- **`init` / `update` / `final` pattern**: each hashing algorithm processes data in a
  streaming fashion rather than loading it all into memory at once, which allows hashing
  files of arbitrary size without being limited by available RAM.
- **Polymorphism via function pointers**: a `t_hash_algo` struct groups the `init`/`update`/
  `final` functions of each algorithm, letting all parsing, input-reading (file/string/stdin),
  and output logic be written once and shared between MD5 and SHA-256.
- **Argument parsing**: flag recognition stops as soon as the first positional argument
  (a filename) is encountered, matching the behavior expected by the subject — a `-s`
  appearing after a filename is then treated as a literal filename rather than an option.

## Coming up

- Symmetric encryption
- Asymmetric encryption
