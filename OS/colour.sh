echo "Enter Background Colour"
read bgcolour
echo "Enter Foreground Colour"
read fgcolour
setterm -term linux -back $bgcolour -fore $fgcolour -clear all
