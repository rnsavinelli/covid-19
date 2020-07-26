# USAGE: graph.R CSVFILE
commandArgs(trailingOnly = TRUE)

data <- read.csv(args[1])
# HEADER
# Country, Cumulative_cases, Cumulative_deaths
png(file="~/graphs/deaths_vs_cases.png", width=800, height=600)
plot(data$Cumulative_cases, data$Cumulative_deaths, main="Cumulative Deaths vs. Cumulative Cases", ylab="Cumulative Deaths" , xlab="Cumulative Cases", type='l', col="green")
dev.off()

png(file="~/graphs/deaths.png", width=800, height=600)
plot(data$New_deaths, main="Deaths per day", ylab="New Deaths" , xlab="Days", type='l', col="red")
dev.off()

png(file="~/graphs/cases.png", width=800, height=600)
plot(data$New_cases, main="Cases per day", ylab="New Cases" , xlab="Days", type='l', col="blue")
dev.off()
