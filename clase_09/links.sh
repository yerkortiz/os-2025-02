#!/bin/bash

# Crear directorios foo y bar
mkdir -p foo bar

# Crear un archivo en foo
echo "Este es el archivo original" > foo/original.txt

# Crear un soft link en bar
ln -s ../foo/original.txt bar/soft_link.txt

# Crear un hard link en bar
ln foo/original.txt bar/hard_link.txt

echo "Archivos y links creados:"
ls -l foo bar

# Borrar los links
rm bar/soft_link.txt bar/hard_link.txt
echo "Links eliminados:"
ls -l foo bar

# Crear los links nuevamente
ln -s ../foo/original.txt bar/soft_link.txt
ln foo/original.txt bar/hard_link.txt
echo "Links recreados:"
ls -l foo bar

# Borrar el archivo original
rm foo/original.txt
echo "Archivo original eliminado:"
ls -l foo bar

# Restaurar el archivo original
echo "Este es el archivo restaurado" > foo/original.txt
echo "Archivo original restaurado:"
ls -l foo bar

# Cambiar permisos del archivo original
chmod 000 foo/original.txt
echo "Permisos cambiados en el archivo original:"
ls -l foo bar

# Restaurar permisos del archivo original
chmod 644 foo/original.txt
echo "Permisos restaurados en el archivo original:"
ls -l foo bar
