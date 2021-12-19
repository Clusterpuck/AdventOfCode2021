#*****************************************************************************
# Filename: findKeyword.sh                                                   *
# Author: Nicholas Wright 12880155                                           *
# Purpose: Search all files in a data directory, and all subdirectories for  *
#         a keyword provided in command line, output search results          *
#          to file "foundresults.txt                                         *
# Date Written: 01/11/21                                                     *
#****************************************************************************/

if [ $# == 1 ]; then
#tests if only one argument provided
#adding -f tag means will accept command even if the file didn't exist
    for file in $(find -type f); do
#-type f restricts search to files only
        if [[ $file == * ]]; then
            grep -E "$1" $file
#adding \b means will search for whole word result only, not part of a word
        fi
    done
else
    echo "You must provide a word to search for"
fi
