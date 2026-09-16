#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'

pass_count=0
fail_count=0

check() {
	local desc="$1"
	local got="$2"
	local expected="$3"

	if [ "$got" == "$expected" ]; then
		pass_count=$((pass_count + 1))
		echo -e "${GREEN}[OK]${RESET} $desc"
	else
		fail_count=$((fail_count + 1))
		echo -e "${RED}[FAIL]${RESET} $desc"
		diff <(echo "$expected") <(echo "$got") | sed 's/^/    /'
	fi
}

echo "Creating ./ft_ssl"
make 
echo "Creation completed: ./ft_ssl created"

echo -e "\n--- Test 1: basic errors ---"

got=$(./ft_ssl)
check "No arguments" "$got" "usage: ft_ssl command [flags] [file/string]"

got=$(./ft_ssl md5 -s)
check "-s without a value" "$got" "ft_ssl: option requires an argument: '-s'"

got=$(./ft_ssl md5 -s "")
check "MD5 empty string" "$got" 'MD5 ("") = d41d8cd98f00b204e9800998ecf8427e'

got=$(./ft_ssl sha256 -s "")
check "SHA256 empty string" "$got" 'SHA256 ("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855'

echo -e "\n--- Test 2: invalid command ---"

expected=$'ft_ssl: Error: \'aaaaaa\' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s'
got=$(./ft_ssl aaaaaa)
check "Invalid command name" "$got" "$expected"

echo -e "\n--- Test 3: basic vectors ---"

got=$(./ft_ssl md5 -s "abc")
check "MD5 \"abc\"" "$got" 'MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72'

got=$(./ft_ssl sha256 -s "abc")
check "SHA256 \"abc\"" "$got" 'SHA256 ("abc") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad'

echo -e "\n--- Test 4: subject examples ---"

echo "(reference only, not counted) openssl / md5sum on '42 is nice':"
echo "42 is nice" | openssl md5
echo "42 is nice" | md5sum

got=$(echo "42 is nice" | ./ft_ssl md5 -p)
check "'42 is nice' -p" "$got" '("42 is nice")= 35f1d6de0302e2086a4e472266efb3a9'

got=$(echo "Pity the living." | ./ft_ssl md5 -q -r)
check "'Pity the living.' -q -r" "$got" "e20c3b973f63482a778f3fd1869b7f25"

echo "And above all," > file

got=$(./ft_ssl md5 file)
check "md5 file" "$got" 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

got=$(./ft_ssl md5 -r file)
check "md5 -r file" "$got" '53d53ea94217b259c11a5a2d104ec58a file'

got=$(./ft_ssl md5 -s "pity those that aren't following baerista on spotify.")
check "-s with apostrophes" "$got" 'MD5 ("pity those that aren'"'"'t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'

expected=$'("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
got=$(echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file)
check "-p file" "$got" "$expected"

expected=$'("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a file'
got=$(echo "but eventually you will understand" | ./ft_ssl md5 -p -r file)
check "-p -r file" "$got" "$expected"

expected=$'("GL HF let\'s go")= d1e3cc342b6da09480b27ec57ff243e2\nMD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
got=$(echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file)
check "-p -s foo file" "$got" "$expected"

expected=$'("one more thing")= a0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 "foo"\n53d53ea94217b259c11a5a2d104ec58a file\nft_ssl: md5: -s: No such file or directory\nft_ssl: md5: bar: No such file or directory'
got=$(echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar" 2>&1)
check "stop_flags: -s after a filename" "$got" "$expected"

expected=$'just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a'
got=$(echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file)
check "-r -q -p -s foo file" "$got" "$expected"

echo "https://www.42.fr/" > website

got=$(./ft_ssl sha256 -q website)
check "sha256 -q website" "$got" "1ceb55d2845d9dd98557b50488db12bbf51aaca5aa9c1199eb795607a2457daf"

got=$(./ft_ssl sha256 -s "42 is nice")
check "sha256 -s '42 is nice'" "$got" 'SHA256 ("42 is nice") = b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f'

echo -e "\n--- Test 5: padding edge cases ---"

got=$(python3 -c "print('a'*55, end='')" | ./ft_ssl md5)
check "55-byte message" "$got" "(stdin)= ef1772b6dff9a122358552954ad0df65"

got=$(python3 -c "print('a'*56, end='')" | ./ft_ssl md5)
check "56-byte message" "$got" "(stdin)= 3b0c8ac703f828b04c6c197006d17218"

got=$(python3 -c "print('a'*63, end='')" | ./ft_ssl md5)
check "63-byte message" "$got" "(stdin)= b06521f39153d618550606be297466d5"

got=$(python3 -c "print('a'*64, end='')" | ./ft_ssl md5)
check "64-byte message" "$got" "(stdin)= 014842d480b571495a4a0363793f7367"

echo -e "\n--- Test 6: whirlpool ---"

got=$(./ft_ssl whirlpool -s "")
check "whirlpool \"\"" "$got" 'WHIRLPOOL ("") = 19fa61d75522a4669b44e39c1d2e1726c530232130d407f89afee0964997f7a73e83be698b288febcf88e3e03c4f0757ea8964e59b63d93708b138cc42a66eb3'

got=$(./ft_ssl whirlpool -s "abc")
check "whirlpool \"abc\"" "$got" 'WHIRLPOOL ("abc") = 4e2448a4c6f486bb16b6562c73b4020bf3043e3a731bce721ae1b303d97e6d4c7181eebdb6c57e277d0e34957114cbd6c797fc9d95d8b582d225292076d4eef5'

got=$(./ft_ssl whirlpool -s "The quick brown fox jumps over the lazy dog")
check "whirlpool sentence" "$got" 'WHIRLPOOL ("The quick brown fox jumps over the lazy dog") = b97de512e91e3828b40d2b0fdce9ceb3c4a71f9bea8d88e75c4fa854df36725fd2b52eb6544edcacd6f8beddfea403cb55ae31f03ad62a5ef54e42ee82c3fb35'

echo -e "\n=================================="
echo -e "Results: ${GREEN}${pass_count} passed${RESET}, ${RED}${fail_count} failed${RESET} (out of $((pass_count + fail_count)))"
echo "=================================="
