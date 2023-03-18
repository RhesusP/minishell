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
- [ ]	Test #9		--> ok but segfault
- [x]	Test #10
- [x]	Test #11
- [x]	Test #12

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

### Test #9
```bash
TOTO=toto
```
Must return
```bash
CMD		ls
ARG		-al
HE		<<
DELIMITER	here
```

### Test #10
```bash
TOTO=toto ls
```
Must return
```bash
CMD		ls
```

### Test #11
```bash
TOTO=toto | ls
```
Must return
```bash
CMD		ls
```

### Test #12
```bash
TOTO=toto|ls
```
Must return
```bash
CMD		ls
```