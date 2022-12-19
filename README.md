# MINISHELL
Собственная имплементация `shell` оболочки.
## Реализованные функции
* Отображает подсказку при ожидании новой команды.
* Имеет рабочую историю.
* Находит и запускает нужный исполняемый файл (на основе переменной `PATH`, или используя.
`относительный`, или `абсолютный путь`)
* Дескриптор `’` (одинарная кавычка), который препятствует интерпретации оболочкой
метасимволов в последовательности, заключенной в кавычки.
* Дескриптор `"` (двойная кавычка), который
препятствует интерпретации оболочкой
метасимволов в последовательности, заключенной в кавычки, за исключением `$` (знака доллара).
* Имплементация перенаправления:
	* `<` перенаправляет ввод
	* `>` перенаправляет вывод
	* `<<` указываем разделитель, затем считывает входные данные до
тех пор, пока не будет видна строка, содержащая разделитель
	* `>>` перенаправляет вывод в режиме добавления
* Реализуйте каналы (`|` символ). Вывод каждой команды в канал соединяется со входом следующей команды через канал.
* Обрабатывает переменные окружения (`$`, за которыми следует последовательность символов), которые заменяются на их значения.
* Обрабатывает `$?`, который заменяется статусом последней выполненной команды.
* Обрабатывает `ctrl-C`, `ctrl-D` и `ctrl-\`, которые ведут себя как в `bash`.
* В интерактивном режиме:
	* `ctrl-C` выводит новое приглашение на новой строке
	* `ctrl-D` завершает работу оболочки
	* `ctrl-\` ничего не делает
* Имплементация `builtins`(встроенные в оболочку команды):
	* `echo` с опцией `-n`
	* `cd` только с `относительным` или `абсолютным путем`
	* `pwd` без опций
	* `export` без опций
	* `unset` без опций
	* `env` без опций и аргументов
	* `exit` без опций

## Зависимости:
* [readline](https://man7.org/linux/man-pages/man3/readline.3.html)

В `Makefile` следует указать путь до `readline` в поле `READLINE_FLAGS`.

### Путь для `Linux`
```Makefile
READLINE_FLAGS= -lreadline
```
### Путь для `macOS`
Замените `<username>` на свой
```Makefile

READLINE_FLAGS= -lreadline -L/Users/<username>/.brew/opt/readline/lib
```

## Компиляция:
```bash
make
```
## Запуск
```bash
chmod +x minishell
./minishell
```
