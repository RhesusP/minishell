## Tests for tokenization

### Current progress

- [ ]	Test #1
- [ ]	Test #2
- [ ]	Test #3
- [ ]	Test #4
- [ ]	Test #5
- [ ]	Test #6
- [ ]	Test #7

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
ARG		bonjout
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
ls -al << here
```
Must create a file named `ls`
```bash
CMD		ls
ARG		-al
HE		<<
DELIMITER	here
```

### Test #8
```bash
TOTO=toto
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
ls -al << here
```
Must create a file named `ls`
```bash
CMD		ls
ARG		-al
HE		<<
DELIMITER	here
```