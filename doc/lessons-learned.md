# Lessons learned

## Why this project matters to me

Cryptography is one of the areas I'm actively focusing on as I go deeper into
cybersecurity, not just knowing that "MD5 is broken" or "SHA-256 is what you should use
instead," but actually understanding *why*: what makes one hash function different from
another internally, what design choices affect their security and performance, and what
it really means for a function to be "one-way" or "collision-resistant" once you've built
one yourself instead of just reading about it.

This project was also, more directly, a way to push my C and general algorithmic skills.
Implementing a well-specified algorithm from a written standard, byte by byte, with no
library to lean on, forces a level of precision that's easy to skip past when just calling
`hashlib.md5()` in a language like Python. Every design decision in this repo the
`init`/`update`/`final` pattern, the polymorphism via function pointers, the streaming
approach to file handling came out of trying to write something correct, not just
something that runs.

## Difficulties

Setting aside typos and copy-paste mistakes, a few genuine conceptual hurdles stood out:

- **Polymorphism in C vs. Python.** Coming from Python, where polymorphism is essentially
  free (the interpreter resolves the right method automatically based on an object's
  type), I had to rebuild that idea from scratch in C. There's no such mechanism built into
  the language, a struct holding function pointers (`t_hash_algo`, with `init`/`update`/
  `final`) is the entire "trick," and understanding that this struct is not some special
  language construct, just an ordinary struct whose fields happen to be addresses of code
  instead of addresses of data, took some real back-and-forth before it clicked.

- **Endianness.** MD5 is little-endian throughout; SHA-256 is big-endian throughout.
  Getting this wrong doesn't crash anything, it silently produces a wrong-but-plausible
  digest. Implementing both algorithms side by side made it very clear how easy it is to
  carry an assumption from one context into another without noticing, and how much that
  reinforced the value of testing against official vectors rather than trusting that "it
  compiles" means "it works."

- **The padding boundary.** The logic for deciding whether the message length field fits
  in the current block, or needs a whole extra block, is a classic off-by-one trap. Working
  through it by hand for a few concrete message lengths (55, 56, 63, 64 bytes) before
  writing the code was what actually made the rule stick, rather than just copying a
  formula from a reference.

- **Streaming design.** My first instinct was to pad the entire message into one big
  buffer before processing it, simple to reason about, but it doesn't scale to large
  files and doesn't reflect how real implementations work. Rebuilding the logic around a
  small fixed-size buffer that gets flushed block by block, with the padding computed only
  once at the very end, was a good exercise in separating "what the algorithm
  conceptually does" from "how to implement it without unnecessary memory use."

## What's next

This hashing module is meant to be the first of three: symmetric and asymmetric
encryption are planned as future additions to this repository. I'm also considering
implementing Whirlpool as a bonus, partly because its internal structure closely mirrors
AES, which I had already implemented from scratch in Python — a good opportunity to
carry that understanding into a new context and reinforce it further.
