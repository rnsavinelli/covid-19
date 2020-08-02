# USAGE: graph.R CSV_DASHBOARD OUT_DIR
args = (commandArgs(TRUE))
out = args[2]

if(length(args) == 0) {
    print("USAGE: graph.R CSV_DASHBOARD")
} else {
    csvfile = args[1]
    data <- read.csv(csvfile)

    setwd(out)
    print("Graphing: Cumulative Deaths vs. Cumulative Cases")
    png(file="cumulativedeaths_vs_cumulativecases.png", width=800, height=600)
    plot(data$Cumulative_cases, data$Cumulative_deaths, main="Cumulative Deaths vs. Cumulative Cases", ylab="Cumulative Deaths" , xlab="Cumulative Cases", type='l', col="green")
    dev.off()
    print("done")

    print("Graphing: Deaths per Census")
    png(file="deaths.png", width=800, height=600)
    plot(data$New_deaths, main="Deaths per Census", ylab="New Deaths" , xlab="Census (days)", type='l', col="red")
    dev.off()
    print("done")

    print("Graphing: Cumulative Deaths per Census")
    png(file="cumulativedeaths.png", width=800, height=600)
    plot(data$Cumulative_deaths, main="Cumulative Deaths per Census", ylab="New Deaths" , xlab="Census (days)", type='l', col="red")
    dev.off()
    print("Done")

    print("Graphing: Cases per Census")
    png(file="cases.png", width=800, height=600)
    plot(data$New_cases, main="Cases per Census", ylab="New Cases" , xlab="Census (days)", type='l', col="blue")
    dev.off()
    print("Done")

    print("Graphing: Cumulative Cases per Census")
    png(file="cumulativecases.png", width=800, height=600)
    plot(data$Cumulative_cases, main="Cumulative Cases per Census", ylab="New Cases" , xlab="Census (days)", type='l', col="blue")
    dev.off()
    print("Done")
}
