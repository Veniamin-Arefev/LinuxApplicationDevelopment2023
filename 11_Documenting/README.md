# Инструкция по эксплуатации

### Compile all sources, update po, create translations etc. `do.sh` may accept first argument as target dir to install program.
#### Default install dir is `/tmp/guessr`
```sh
  chmod +x do.sh
  source ./do.sh
```

### To uninstall run this
```sh
 make uninstall
```

### Run with specific translation
#### Change dir to your installation. For default `cd /tmp/guessr`
```sh
  LC_ALL=ru_RU.UTF-8 ./bin/guessr
```

### Create russian translation file
```sh
  msginit -i po/guessr.pot -o po/ru.po -l ru_RU.UTF-8
```

