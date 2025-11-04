#!/bin/bash

mkdir -p foo bar

echo "Este es el archivo original" > foo/original.txt

ln -s ../foo/original.txt bar/soft_link.txt

ln foo/original.txt bar/hard_link.txt
echo "Archivos y links creados:"
ls -l foo bar

rm bar/soft_link.txt bar/hard_link.txt
echo "Links eliminados:"
ls -l foo bar

ln -s ../foo/original.txt bar/soft_link.txt
ln foo/original.txt bar/hard_link.txt
echo "Links recreados:"
ls -l foo bar

rm foo/original.txt
echo "Archivo original eliminado:"
ls -l foo bar

echo "Este es el archivo restaurado" > foo/original.txt
echo "Archivo original restaurado:"
ls -l foo bar

chmod 000 foo/original.txt
echo "Permisos cambiados en el archivo original:"
ls -l foo bar

chmod 644 foo/original.txt
echo "Permisos restaurados en el archivo original:"
ls -l foo bar
