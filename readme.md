## Detection tests for env variables

```bash
echo $TEST | echo "$TEST" | echo $'TEST' | echo "'$TEST'" | echo '"$TEST"' | echo
```
## Split tests

```bash
echo coucou salut
```
`get_next_token()` must print `4 11 17`