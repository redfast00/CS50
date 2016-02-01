Google maps + Google news mashup
--------------------------------

In order to be able to search for words of 2 letters (like admin_code1), 
the following command was executed:

```bash
sudo tee /etc/mysql/conf.d/pset8.cnf <<EOF
[mysqld]
ft_min_word_len = 2
EOF
```