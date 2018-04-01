Input format:
first string - parent
second string - children

e.g.

                            8
                          /    \
                        bar      baz
                       / |  \       |  \
                  3.5   20   str   foo   bye
                  |                        |
                  9                       cya

must be:
8
bar baz
bar
3.5 20 str
3.5
9
baz
foo bye
bye
cya
