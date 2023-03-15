## Tests for tokenization

```bash
> ls
```
Must create a file named `ls`
```bash
RO			>
FILEPATH	ls
```


```bash
echo "bonjour toi" | ls > file
```

```bash
CMD			echo
ARG			"bonjour toi"
PIPE		|
CMD			ls
RO			>
FILEPATH	file

```