## Tests for tokenization

### Current progress

- [x]	Test #1
- [x]	Test #2
- [x]	Test #3
- [x]	Test #4
- [x]	Test #5
- [x]	Test #6
- [x]	Test #7
- [x]	Test #8
- [x]	Test #9
- [x]	Test #10
- [x]	Test #11
- [x]	Test #12
- [x]	Test #13
- [x]	Test #14
- [x]	Test #15

### Test #1
```bash
echo coucou
```
Must return
```bash
CMD		echo
ARG		coucou
```

### Test #2
```bash
echo coucou "ca va ?" oui
```
Must return
```bash
CMD		echo
ARG		coucou
ARG		"ca va ?"
ARG		oui
```

### Test #3
```bash
echo coucou | ls -al
```
Must return
```bash
CMD		echo
ARG		coucou
PIPE		|
CMD		ls
ARG		-al
```

### Test #4
```bash
echo "bonjour toi" | ls > file
```
Must return
```bash
CMD		echo
ARG		"bonjour toi"
PIPE		|
CMD		ls
RO		>
FILEPATH	file
```

### Test #5
```bash
echo “salut toi” bonjour | ls -al > file
```
Must return
```bash
CMD		echo
ARG		"salut toi"
ARG		bonjour
PIPE		|
CMD		ls
ARG		-al
RO		>
FILEPATH	file
```

### Test #6
```bash
> ls
```
Must create a file named `ls`
```bash
RO		>
FILEPATH	ls
```

### Test #7
```bash
>ls
```
Must create a file named `ls`
```bash
RO		>
FILEPATH	ls
```

### Test #8
```bash
ls -al << here
```
Must create a file named `ls`
```bash
CMD		ls
ARG		-al
HE		<<
DELIMITER	here
```

## Tests for variable assignation

### Test #9
```bash
TOTO=toto
```
`t_word` must be empty and TOTO is set in global variables.

### Test #10
```bash
ls TOTO=toto
```
Variable assignation is ignored and must return
```bash
CMD		ls
ARG		TOTO=toto
```

### Test #11
```bash
TOTO=toto ls
```
Variable assignation is ignored and must return
```bash
CMD		ls
```

### Test #12
```bash
ls | TOTO=toto
```
Variable assignation is ignored and must return
```bash
CMD		ls
```

### Test #13
```bash
TOTO=toto | ls
```
Variable assignation is ignored and must return
```bash
CMD		ls
```

### Test #14
```bash
echo | TOTO=toto | ls
```
Variable assignation is ignored and must return
```bash
CMD		echo
PIPE		|
CMD		ls
```

### Test #15
```bash
echo salut | TOTO=toto | TATA=tata | ls
```
Variable assignation is ignored and must return
```bash
CMD		echo
ARG		salut
PIPE		|
CMD		ls
```

