#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
PURPLE='\033[0;35m'

VALGRIND_FLAGS="valgrind --trace-children=yes --leak-check=full -s"

make

echo -e "\n-------------------------\n"
echo -e "Starting mandatory test..\n"

echo -e "${PURPLE}One simple pipe 1${NC}"
./pipex tests/infile "cat" "wc -l" tests/one_pipe_no_err/mypipex
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/infile cat | wc -l > tests/one_pipe_no_err/original
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/one_pipe_no_err/mypipex tests/one_pipe_no_err/original)
$VALGRIND_FLAGS ./pipex tests/infile "cat" "wc -l" tests/one_pipe_no_err/mypipex 2> tests/one_pipe_no_err/leaks

echo -e "${YELLOW} ./pipex tests/infile "cat" "wc -l" tests/one_pipe_no_err/mypipex${NC}"
echo -e "${YELLOW} < tests/infile cat | wc -l > tests/one_pipe_no_err/original${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/one_pipe_no_err/leaks${NC}\n"

# Test 2
echo -e "${PURPLE}One simple pipe 2${NC}"
./pipex tests/infile "tr 'a-z' 'A-Z'" "rev" tests/one_pipe_no_err2/mypipex
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/infile tr a-z A-Z | rev > tests/one_pipe_no_err2/original
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/one_pipe_no_err2/mypipex tests/one_pipe_no_err2/original)
$VALGRIND_FLAGS ./pipex tests/infile "tr 'a-z' 'A-Z'" "rev" tests/one_pipe_no_err2/mypipex 2> tests/one_pipe_no_err2/leaks

echo -e "${YELLOW} ./pipex tests/infile "tr 'a-z' 'A-Z'" "rev" tests/one_pipe_no_err2/mypipex${NC}"
echo -e "${YELLOW} < tests/infile tr a-z A-Z | rev > tests/one_pipe_no_err2/original${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/one_pipe_no_err2/leaks${NC}\n"

# Test 3
echo -e "${PURPLE}Command not found${NC}"
./pipex tests/infile "nonexistentcmd" "cat" tests/cmd_not_found/mypipex
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/infile nonexistentcmd | cat > tests/cmd_not_found/original
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/cmd_not_found/mypipex tests/cmd_not_found/original)
$VALGRIND_FLAGS ./pipex tests/infile "nonexistentcmd" "cat" tests/cmd_not_found/mypipex 2> tests/cmd_not_found/leaks

echo -e "${YELLOW} ./pipex tests/infile "nonexistentcmd" "cat" tests/cmd_not_found/mypipex${NC}"
echo -e "${YELLOW} < tests/infile nonexistentcmd > cat tests/cmd_not_found/original${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/cmd_not_found/leaks${NC}\n"

# Test 4
echo -e "${PURPLE}No file${NC}"
./pipex nofile "cat" "wc -l" tests/no_file/mypipex
EXIT_CODE_MY_PIPEX=$(echo $?)
< no_file "cat" | wc -l > tests/no_file/original
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/no_file/mypipex tests/no_file/original)
$VALGRIND_FLAGS ./pipex nofile "cat" "wc -l" tests/no_file/mypipex 2> tests/no_file/leaks

echo -e "${YELLOW} /pipex tests/nofile "cat" "wc -l" tests/no_file/mypipex${NC}"
echo -e "${YELLOW} < tests/no_file cat | wc -l > tests/no_file/original${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/cmd_not_found/leaks${NC}\n"

# Test 5
echo -e "${PURPLE}No permissions to write${NC}"
./pipex tests/infile "cat" "wc -l" tests/no_perm_to_write/mypipex_no_perm
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/infile "cat" | wc -l > tests/no_perm_to_write/original_no_perm
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/no_perm_to_write/mypipex_no_perm tests/no_perm_to_write/original_no_perm)
$VALGRIND_FLAGS ./pipex infile "cat" "wc -l" tests/no_perm_to_write/mypipex_no_perm 2> tests/no_perm_to_write/leaks

echo -e "${YELLOW} /pipex tests/nofile "cat" "wc -l" tests/no_perm_to_write/mypipex_no_perm${NC}"
echo -e "${YELLOW} < tests/no_file cat | wc -l > tests/no_perm_to_write/original_no_perm${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/no_perm_to_write/leaks${NC}\n"

# Test 6 
echo -e "${PURPLE}No permissions to read${NC}"
./pipex tests/no_perm_to_read/no_perm "cat" "wc -l" tests/no_perm_to_read/mypipex_no_perm
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/no_perm_to_read/no_perm "cat" | wc -l > tests/no_perm_to_read/original_no_perm
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/no_perm_to_read/mypipex_no_perm tests/no_perm_to_read/original_no_perm)
$VALGRIND_FLAGS ./pipex infile "cat" "wc -l" tests/no_perm_to_read/mypipex_no_perm 2> tests/no_perm_to_read/leaks

echo -e "${YELLOW} /pipex tests/nofile "cat" "wc -l" tests/no_perm_to_read/mypipex_no_perm${NC}"
echo -e "${YELLOW} < tests/no_file cat | wc -l > tests/no_perm_to_read/original_no_perm${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/no_perm_to_write/leaks${NC}\n"

# Test 7
echo -e "${PURPLE}Absolute path${NC}"
./pipex tests/infile "/bin/cat" "/usr/bin/wc -l" tests/abs_path/mypipex
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/infile /bin/cat | /usr/bin/wc -l > tests/abs_path/original
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/abs_path/mypipex tests/abs_path/original)
$VALGRIND_FLAGS ./pipex tests/infile "cat" "wc -l" tests/abs_path/mypipex_no_perm 2> tests/abs_path/leaks

echo -e "${YELLOW} /pipex tests/infile "cat" "wc -l" tests/abs_path/mypipex_no_perm${NC}"
echo -e "${YELLOW} < tests/infile cat | wc -l > tests/abs_path/original_no_perm${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/abs_path/leaks${NC}\n"

# Test 8
echo -e "${PURPLE}Error mid_cmd${NC}"
./pipex tests/infile "error" "cat" tests/err_mid_cmd/mypipex
EXIT_CODE_MY_PIPEX=$(echo $?)
< tests/infile error | cat > tests/err_mid_cmd/original
EXIT_CODE_ORI=$(echo $?)
RESULT=$(diff  tests/err_mid_cmd/mypipex tests/err_mid_cmd/original)
$VALGRIND_FLAGS ./pipex tests/infile "error" "cat" tests/err_mid_cmd/mypipex_no_perm 2> tests/err_mid_cmd/leaks

echo -e "${YELLOW} /pipex tests/infile "error" "cat" tests/err_mid_cmd/mypipex_no_perm${NC}"
echo -e "${YELLOW} < tests/infile error | cat > tests/err_mid_cmd/original_no_perm${NC}"
if [ -z "$RESULT" ]; then
    echo -e "✅ ${GREEN}Output correct${NC}"
else
    echo -e "❌ ${RED}Output incorrect${NC}"
    echo "$RESULT"
fi

if [ $EXIT_CODE_MY_PIPEX == $EXIT_CODE_ORI ]; then
    echo -e "✅ ${GREEN}Exit code correct${NC}"
else
    echo -e "❌ ${RED}Exit code incorrect${NC}"
    echo "$RESULT"
fi
echo -e "${YELLOW}Leaks result in tests/err_mid_cmd/leaks${NC}\n"

make fclean