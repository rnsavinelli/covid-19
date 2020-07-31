#!/bin/bash
# USAGE: ./graph.sh ROUT_DIR CSV_INPUT_FILENAME

if [ $# -lt 2 ]; then
    echo "USAGE: ./graph.sh ROUT_DIR CSV_INPUT_FILENAME"
    exit 1
fi

datadir="./dashboards"
selection=""

outdir=$1
inputfile=$2

mkdir -p $outdir

listandReturn() {
    printf "Listing contents of %s\\n" "$1"
    case "$(ls -d "$1"/*/ | wc -l)" in
        0) echo "There's nothing to list." && exit 1 ;;
        *) ls -drc "$1"/*/ | awk -F '/' '{print $3}' | nl ;;
    esac
    read -erp "Pick an entry by number to plot, or press Ctrl-C to cancel. " number
    [[ "$number" -lt "1" ]] || [[ "$number" -gt "$(ls -d "$1"/*/ | wc -l)" ]] && printf "Error: Invalid selection.\\nAborting execution.\\n" && exit 1
    selection="$(ls -drc "$1"/*/ | awk -F '/' '{print $3}' | nl | grep -w "$number" | awk '{print $2}')"
}

listandReturn $datadir
printf "Rscript graph.R %s/%s/%s:\\n" $datadir $selection $inputfile

Rscript graph.R $datadir/$selection/$inputfile $outdir

printf "Saving files to %s/%s... " $datadir $selection
mv $outdir/* $datadir/$selection/
printf "done.\\n"
