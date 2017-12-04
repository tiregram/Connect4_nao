library(plotly)
data <- read.csv(file="League.csv", header=TRUE, sep=",")

data$P1depth <-  as.numeric(as.character(data$P1depth))
data$P1weight <-  as.numeric(as.character(data$P1weight))
data$P2depth <-  as.numeric(as.character(data$P2depth))
data$P2weight <-  as.numeric(as.character(data$P2weight))
data$TotalChips <- as.numeric(as.character(data$TotalChips))
data$Starter <- as.character(data$Starter)
data$Winner <- as.character(data$Winner)



data$IA1 <- paste(data$P1name,data$P1weight,data$P1depth,sep="_")
data$IA2 <- paste(data$P2name,data$P2weight,data$P2depth,sep="_")
data$WIA[data$Winner==data$P1color] <-  data$IA1[data$Winner==data$P1color]
data$WIA[data$Winner==data$P2color] <-  data$IA2[data$Winner==data$P2color]
data$WIA[data$Winner=="No one"] <-  "No One"


dataSelector <- (data$P1name != data$P2name)
data2 <- data[dataSelector,]


data2$P1depth <-  as.numeric(as.character(data2$P1depth))
data2$P1weight <-  as.numeric(as.character(data2$P1weight))
data2$P2depth <-  as.numeric(as.character(data2$P2depth))
data2$P2weight <-  as.numeric(as.character(data2$P2weight))
data2$TotalChips <- as.numeric(as.character(data2$TotalChips))
data2$Starter <- as.character(data2$Starter)
data2$Winner <- as.character(data2$Winner)
data2$IA1 <- paste(data2$P1name,data2$P1weight,data2$P1depth,sep="_")
data2$IA2 <- paste(data2$P2name,data2$P2weight,data2$P2depth,sep="_")
data2$WIA[data2$Winner==data2$P1color] <-  data2$IA1[data2$Winner==data2$P1color]
data2$WIA[data2$Winner==data2$P2color] <-  data2$IA2[data2$Winner==data2$P2color]
data2$WIA[data2$Winner=="No one"] <-  "No One"



D <- 3:4
W <- 4:6
IA <- levels(data$P1name)
D.l = length(D)
W.l = length(W)
IA.l = length(IA)

nb.ia <- IA.l * W.l * D.l
nb.combat <- 118

nb.vs <- (nb.ia * (nb.ia-1) ) / 2
nb.fight <- nb.vs * nb.combat

if(length(data[,1])!=nb.fight)
  print("message error")

# win
win.start  <- data$Winner == data$Starter
lose.start <- data$Winner != data$Starter & data$Winner != "No one"
draw.start <- data$Winner == "No one"
datawiner  <-  data[win.start,]
datalooser <-  data[lose.start,]
datadraw   <-  data[draw.start,]
win = length(datawiner[,1])/length(data[,1])
defeat = length(datalooser[,1])/length(data[,1])
draw = length(datadraw[,1])/length(data[,1])
win + defeat + draw

freqwin1 = table(data$IA2,data$WIA)
freqwin2 = table(data$IA1,data$WIA)
freqwin = freqwin1 + freqwin2

freqwin <- freqwin[,0:18]
l <- lower.tri(freqwin)
u <- upper.tri(freqwin)

r = freqwin[l]/t(freqwin)[l]
freqwin[l]=t(freqwin)[l]

m=matrix(-1,18,18)
m[l] = r
freqwin[l] = r
fr

