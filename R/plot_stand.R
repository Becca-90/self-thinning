plot_stand <- function(data, xvar, yvar, title="") {
  
  data[["x"]] <- data[[xvar]] ##which column name for what we want to plot against density
  data[["y"]] <- data[[yvar]] ##plot density or other
  
  data %>% 
    filter(time > 0.1) %>%
    ggplot(aes(x, y, col = trait_value, label = trait_value)) + 
    geom_line() + 
    xlab(xvar) +
    ylab(yvar) +
    theme_classic(base_size = 18) +
    ggtitle(title)
}