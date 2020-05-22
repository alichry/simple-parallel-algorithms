#!/usr/bin/php
<?php

define('ARG_INT_MIN', 'INT_MIN');
define('ARG_INT_MAX', 'INT_MAX');

function printUsage() {
    global $argv;
    $basename = basename($argv[0]);
    echo "USAGE:\n\t$basename <size> [cols] [min] [max]\n";
    echo "Where\n";
    echo "\tsize: the array length\n";
    echo "\tcols: number of columns per line, use 0 for no line wrapping\n";
    echo "\tmin: each number in the array will be bigger or equal than min\n";
    echo "\tmax: each number in the array will be smaller or equal than max\n";
    echo "Possible values of min|max:\n";
    echo "\tA real number,\n";
    echo "\tINT_MIN (for min value)\n";
    echo "\tINT_MAX (for max value)\n";
}

$size = (int) ($argv[1] ?? null);
$cols = (int) ($argv[2] ?? null);
$min = $argv[3] ?? null;
$max = $argv[4] ?? null;
if (!isset($size)) {
    echo "Error, bad arguments!\n";
    printUsage();
    die;
}

if ($cols < 0) {
    echo "Error: bad cols values\n";
    printUsage();
    die;
}

if ($min === ARG_INT_MIN || null === $min) {
    $min = PHP_INT_MIN;
}
if ($max === ARG_INT_MAX || null === $max) {
    $max = PHP_iNT_MAX;
}

if (!ctype_digit($min)) {
    echo "Error, bad min value!\n";
    printUsage();
    die;
}
if (!ctype_digit($max)) {
    echo "Error, bad max value\n";
    printUsage();
    die;
}

if (0 === $size || null === $size) {
    printUsage();
    die;
}

echo "$size\n";
$count = 0;
for ($i = 0; $i < $size; $i++) {
    if ($count == $cols) {
        echo "\n";
        $count = 0;
    }
    $num = random_int($min, $max);
    echo $num;
    $count++;
    if ($i !== $size - 1) {
        echo " ";
    }
}
echo "\n";
?>
