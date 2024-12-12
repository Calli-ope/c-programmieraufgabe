# Programmieraufgabe

## Aufgabe
Vergleich sequenzieller und paralleler Sortierung der großen Datenmengen

## Struktur
Die Struktur des Projekts ist wie folgt:
- `com/` - Quellcode der gemeinsamen Funktionen
- `seq/` - Quellcode der sequenziellen Sortierung
- `par/` - Quellcode der parallelen Sortierung
Log-Dateien werden in den jeweiligen Ordnern gespeichert.

## Nutzung
```bash
# Kompilieren und ausführen
make run -f # par.make oder seq.make

# Reinigen
make clean -f # par.make oder seq.make
```

## Anmerkungen
Unter 100.000 zu sortierenden Knoten ist die Ausführungszeit zu gering, damit sie von der `clock` Funktion gemessen werden kann.
