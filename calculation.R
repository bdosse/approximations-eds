library(latex2exp)

# Don't forget to set working directory to
# the folder containing the batches.

dirs <- list.dirs()
batches <- length(dirs)

approx <- c()

for (i in 2:batches)
{
  files <- list.files(dirs[i])
  N <- length(files)
  
  abs_err <- c()
  
  for (j in 1:N)
  {
    data <- read.csv(paste(dirs[i], "/", files[j], sep=""))
    data <- subset(data, select = -4)
    
    T <- nrow(data)
    
    abs_err <- c(abs_err, abs(data[T, 3] - data[T, 2]))
    
    # If we want to produce a plot, here's what we need:
    jpeg(paste(dirs[i], "/", "plot", j, ".jpg", sep=""))
    plot(x = data[,1], y = data[,3], 
         type = 'l', 
         xlab = "Temps", ylab = "Position")
    lines(x = data[,1], y = data[,2], type = 'l', col = 'red')
    dev.off()
  }
  approx <- c(approx, 1/N * sum(abs_err))
}


mu <- 1/(batches - 1) * sum(approx)
mu

if (batches > 2)
{
  sigma2 <- 1/(batches - 2) * sum((approx - mu)^2)
  sigma2
}


