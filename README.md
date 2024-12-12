# Programmieraufgabe

## Aufgabe
Vergleich sequenzieller und paralleler Sortierung der großen Datenmengen

## Struktur
Die Struktur des Projekts ist wie folgt:
- `com/` - Quellcode der gemeinsamen Funktionen
- `seq/` - Quellcode der sequenziellen Sortierung
- `par/` - Quellcode der parallelen Sortierung

## Nutzung
```bash
# Kompilieren und ausführen
make run -f # par.make oder seq.make

# Reinigen
make clean -f # par.make oder seq.make
```

## Anmerkungen
Beim erneuten bauen sollte `make clean` ausgeführt werden, um alte Dateien zu löschen.