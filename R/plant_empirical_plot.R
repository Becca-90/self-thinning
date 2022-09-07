plant_empirical_plot <- function(data1, data2, xvar, yvar, label1 = "", label2 = "") {
  
  vars <- c(xvar, yvar)
  labels <- tibble(name = vars, label = c(label1, label2))
  
  ggplot() +
    geom_point(data = data1, aes(xvar, yvar, group = node), col = "grey", size = 0.5) +
    geom_line(data = data2, aes(xvar, yvar, group = node), col = "green") +
    facet_wrap(~label, scales = "free") +
    scale_x_log10() +
    scale_y_log10() +
    theme_classic()
}
