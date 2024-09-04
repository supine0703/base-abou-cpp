#!/bin/sh

# if [ "$1" = "rebuild" ]; then
#     ./build.sh
# fi

cd install/test
echo "> ${PWD}/shared_test"
chmod +x shared_test && ./shared_test

echo "\n> ${PWD}/static_test"
chmod +x static_test && ./static_test
echo "\n"
