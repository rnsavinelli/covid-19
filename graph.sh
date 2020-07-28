#!/bin/bash

dir="./dashboards"
out="Rout"
selection=""

mkdir -p $out

listandReturn() {
    printf "Listing contents of %s\\n" "$1"
    case "$(ls -d "$1"/*/ | wc -l)" in
        0) echo "There's nothing to list." && exit 1 ;;
        *) ls -drc "$1"/*/ | awk -F '/' '{print $3}' | nl ;;
    esac
    read -erp "Pick an entry by number to plot, or press Ctrl-C to cancel. " number
    selection="$(ls -drc "$1"/*/ | awk -F '/' '{print $3}' | nl | grep -w "$number" | awk '{print $2}')"
}

listandReturn $dir
#[[ "$selection" -lt "1" ]] || [[ "$selection" -gt "$(ls -d "$1"/*/ | wc -l)" ]] && printf "Error: Invalid selection.\\nAborting execution.\\n" && exit 1

printf "Rscript graph.R ./dashboards/%s/dashboard.csv:\\n" $selection
Rscript graph.R ./dashboards/$selection/dashboard.csv
printf "Saving files to %s/%s... " $dir $selection
mv Rout/* $dir/$selection/
printf "done.\\n"
