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
baz</br>
foo bye</br>
3.5</br>
9</br>
bye</br>
cya</br>

also input file must followed by BFS rules like in example above</br>
for example:</br>
8</br>
bar baz</br>
next step is to describe every child of "8" node:</br>
bar</br>
3.5 20 str</br>
baz</br>
foo bye</br>

and so on
