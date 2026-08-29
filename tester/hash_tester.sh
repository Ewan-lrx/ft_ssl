#!/bin/bash

echo "Creating ./ft_ssl"
if [ ! -f ./ft_ssl ]
then
	make
	echo "Creation completed: ./ft_ssl created"
else
	make
fi
echo "\nTest 1:\nNo arguments (./ft_ssl):"
./ft_ssl
echo "\nTesting: ./ft_ssl md5 -s"
./ft_ssl md5 -s
echo "\nTesting empty strings:"
./ft_ssl md5 -s ""
echo "Expected: MD5 ('') = d41d8cd98f00b204e9800998ecf8427e"
./ft_ssl sha256 -s ""
echo "Expected: SHA256 ('') = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
echo "\nTest 2:\nWrong hashing name (./ft_ssl aaaaaa):"
./ft_ssl aaaaaa
echo "\nTest 3:\nHashing "abc" (./ft_ssl):"
./ft_ssl md5 -s "abc"
echo "Expected: MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72"
./ft_ssl sha256 -s "abc"
echo "Expected: SHA256 ("abc") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
echo "\nTest 4: Subject examples"
echo "\nTesting '42 is nice' with openssl md5/md5sum/my own"
echo "42 is nice" | openssl md5
echo "42 is nice" | md5sum
echo "42 is nice" | ./ft_ssl md5 -p
echo "\nTesting 'Pity the living' md5 -q -r"
echo "Expected: e20c3b973f63482a778f3fd1869b7f25"
echo "Pity the living." | ./ft_ssl md5 -q -r
echo "\nTesting 'And above all,' > file (md5)"
echo "Expected: MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
echo "My result:"
echo "And above all," > file
./ft_ssl md5 file
echo "\nTesting: ./ft_ssl md5 -s 'pity those that aren't following baerista on spotify.'"
echo "Expected: MD5 ('pity those that aren't following baerista on spotify.') = a3c990a1964705d9bf0e602f44572f5f"
echo "My result:"
./ft_ssl md5 -s "pity those that aren't following baerista on spotify."
echo "\nTesting: echo 'be sure to handle edge cases carefully' | ./ft_ssl md5 -p file"
echo "Expected:\n("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
echo "My result:"
echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file
echo "\nTesting: echo 'but eventually you will understand' | ./ft_ssl md5 -p -r file"
echo "Expected:\n('but eventually you will understand')= dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file"
echo "My result:"
echo "but eventually you will understand" | ./ft_ssl md5 -p -r file
echo "\nTesting:  echo 'GL HF let's go' | ./ft_ssl md5 -p -s "foo" file"
echo "Expected:\n('GL HF let's go')= d1e3cc342b6da09480b27ec57ff243e2
MD5 ('foo') = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
echo "My result:"
echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file
echo "\nTesting: echo 'one more thing' | ./ft_ssl md5 -r -p -s 'foo' file -s 'bar'"
echo "Expected:\n('one more thing')= a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 'foo'
53d53ea94217b259c11a5a2d104ec58a file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory"
echo "My result:"
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"
echo "\nTesting: echo 'just to be extra clear' | ./ft_ssl md5 -r -q -p -s 'foo' file"
echo "Expected:\njust to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a"
echo "My result:"
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file
echo "https://www.42.fr/" > website
./ft_ssl sha256 -q website
./ft_ssl sha256 -s "42 is nice"
echo "\nTest 5: Padding edge cases"
echo "\nTesting: 55 bytes message"
echo "Expected: ef1772b6dff9a122358552954ad0df65"
python3 -c "print('a'*55, end='')" | ./ft_ssl md5
echo "\nTesting: 56 bytes message"
echo "Expected: 3b0c8ac703f828b04c6c197006d17218"
python3 -c "print('a'*56, end='')" | ./ft_ssl md5
echo "\nTesting: 63 bytes message"
echo "Expected: b06521f39153d618550606be297466d5"
python3 -c "print('a'*63, end='')" | ./ft_ssl md5
echo "\nTesting: 64 bytes message"
echo "Expected: 014842d480b571495a4a0363793f7367"
python3 -c "print('a'*64, end='')" | ./ft_ssl md5
