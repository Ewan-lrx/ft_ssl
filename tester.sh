#!/bin/bash

echo "Creating ./ft_ssl"
make re
echo "Creation completed: ./ft_ssl created"
echo -e "\nTest 1:\nNo arguments (./ft_ssl):"
./ft_ssl
echo -e "\nTest 2:\nWrong hashing name (./ft_ssl aaaaaa):"
./ft_ssl aaaaaa

