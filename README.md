# Minishell

## CFG rules

```RE
expression = 
	term '|' expression |
	term > expression |
	term < expression |
	term >> expression |
	term << expression |
	term
```
```php
	term = {$}? ([a-z]|[A-Z]|[0-9]|{~, "`", "!", "@", "#", '$', "%", "^", "&", "*", "(", ")", "-", "_", "+", "=", "{", "}", "[", "]", "|", \, ";", ":", "\"", "'", "<", ">", ".", ',', "?", "/"})*
```
