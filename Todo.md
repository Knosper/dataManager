Datenbanken auflisten:
Implement threading or asynchronous I/O to handle multiple scan tasks concurrently.
Verwenden Sie eine SQL-Abfrage, um alle Datenbanken auf dem Server zu ermitteln. Sie können die Systemtabelle sys.databases verwenden, um die Namen der Datenbanken zu erhalten1.
Führen Sie eine Abfrage wie diese aus:
SELECT name FROM sys.databases;

# Datenbanken auflisten:

## implement second search method:


- systemctl status postgresql (detect db on sys)