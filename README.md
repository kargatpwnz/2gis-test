Input format:
first string - parent</br>
second string - children</br>

e.g.

                            8
                          /    \
                        bar      baz
                       / |  \       |  \
                  3.5   20   str   foo   bye
                  |                        |
                  9                       cya

must be:</br>
8</br>
bar baz</br>
bar</br>
3.5 20 str</br>
3.5</br>
9</br>
baz</br>
foo bye</br>
bye</br>
cya</br>
