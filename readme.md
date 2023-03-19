## Tests for tokenization

### Current progress

- [ ]	Test #1
- [ ]	Test #2
- [ ]	Test #3
- [ ]	Test #4
- [ ]	Test #5
- [ ]	Test #6
- [ ]	Test #7
- [ ]	Test #8
- [ ]	Test #9
- [ ]	Test #10
- [ ]	Test #11
- [ ]	Test #12
- [ ]	Test #13
- [ ]	Test #14
- [ ]	Test #15

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

