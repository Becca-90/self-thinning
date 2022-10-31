Testing integration via integrate_over_size_distribution
================
2022-07-26

``` r
library(plant)
library(dplyr)
```

    ## 
    ## Attaching package: 'dplyr'

    ## The following objects are masked from 'package:stats':
    ## 
    ##     filter, lag

    ## The following objects are masked from 'package:base':
    ## 
    ##     intersect, setdiff, setequal, union

``` r
library(tidyr)
library(ggplot2)
library(purrr)
```

Let’s assume a known density wrt height, to test against. Let

![n(H)= a H^{-b}](https://latex.codecogs.com/png.image?%5Cdpi%7B110%7D&space;%5Cbg_white&space;n%28H%29%3D%20a%20H%5E%7B-b%7D "n(H)= a H^{-b}")

Then we can directly integrate to compare results against ‘plant’
integration

![N= \int\_{1}^{20} n(H) \\, dH = a \bigg\[\frac{H^{1-b}}{1-b}\bigg\]^{20}\_{1}](https://latex.codecogs.com/png.image?%5Cdpi%7B110%7D&space;%5Cbg_white&space;N%3D%20%5Cint_%7B1%7D%5E%7B20%7D%20n%28H%29%20%5C%2C%20dH%20%3D%20a%20%5Cbigg%5B%5Cfrac%7BH%5E%7B1-b%7D%7D%7B1-b%7D%5Cbigg%5D%5E%7B20%7D_%7B1%7D "N= \int_{1}^{20} n(H) \, dH = a \bigg[\frac{H^{1-b}}{1-b}\bigg]^{20}_{1}")

![H\_{T}= \int\_{1}^{20}N(H) \\, H \\, dH = a \bigg\[\frac{H^{2-b}}{2-b}\bigg\]^{20}\_{1}](https://latex.codecogs.com/png.image?%5Cdpi%7B110%7D&space;%5Cbg_white&space;H_%7BT%7D%3D%20%5Cint_%7B1%7D%5E%7B20%7DN%28H%29%20%5C%2C%20H%20%5C%2C%20dH%20%3D%20a%20%5Cbigg%5B%5Cfrac%7BH%5E%7B2-b%7D%7D%7B2-b%7D%5Cbigg%5D%5E%7B20%7D_%7B1%7D "H_{T}= \int_{1}^{20}N(H) \, H \, dH = a \bigg[\frac{H^{2-b}}{2-b}\bigg]^{20}_{1}")

Now generate data to tests

``` r
## set density = a*H^-b, height sequence 1:20, b = 3/2, a = starting density per unit area
## create stand of individuals with heights obtained and resulting density over time
## so we have constant height growth increase, therefore assume time steps are non-linear

a = 10
b = 3/2
plant_stand <- 
  tibble(
    time = 1,
    step=2,
    patch_density = 1, 
    species = 1, 
    height = seq(20,1, by = -0.05)
    ) %>% 
  mutate(
    cohort = seq_len(n()) %>% rev(),
    density = a*height^(-b)
  )
```

Now compare solutions

``` r
# integrate with plant inbuilt solver
stand_integrate <- integrate_over_size_distribution(plant_stand)

# Analyitcal soluntions
# N: a/(1-b) H ^ (1-b)
# H: a/(2-b) H ^ (2-b)

N_analytical <- a/(1-b) *20 ^ (1-b) - a/(1-b) *1 ^ (1-b)
N_trapezium <- -plant:::trapezium(plant_stand$height, plant_stand$density)
N_plant<- stand_integrate$individuals

c(N_analytical, N_trapezium, N_plant)
```

    ## [1]  15.52786  15.53099 241.21153

``` r
H_analytical <- a/(2-b) *20 ^ (2-b) - a/(2-b) *1 ^ (2-b)
H_trapezium <- -plant:::trapezium(plant_stand$height, plant_stand$height*plant_stand$density)
H_plant <- stand_integrate$height

c(H_analytical, H_trapezium, H_plant)
```

    ## [1] 69.44272 69.44375 69.44375

``` r
Hav_analytical <- H_analytical/N_analytical
Hav_trapezium <- H_trapezium/N_trapezium
Hav_plant <- H_plant/N_plant

c(Hav_analytical, Hav_trapezium, Hav_plant)
```

    ## [1] 4.4721360 4.4713033 0.2878956

So it turns out `integrate_over_size_distreibution` is getting the
number of individuals wrong which is flowing onto average height

Here’s a fix:

``` r
integrate_over_size_distribution2 <- function (tidy_species_data) 
{
    tidy_species_data %>% dplyr::select(-.data$cohort) %>% stats::na.omit() %>% 
        dplyr::filter(.data$step > 1) %>% dplyr::group_by(.data$step, 
        .data$time, .data$patch_density, .data$species) %>% 
    dplyr::summarise(
      density_integrated = -plant:::trapezium(.data$height, .data$density), 
      min_height = min(.data$height),
      dplyr::across(where(is.double) & !c(density, density_integrated, min_height) , ~-plant:::trapezium(height, density * .x)), 
        .groups = "drop") %>% 
    rename(density = density_integrated)
}

integrate_over_size_distribution2(plant_stand) %>% 
  mutate(Hav = height/density)
```

    ## # A tibble: 1 × 8
    ##    step  time patch_density species density min_height height   Hav
    ##   <dbl> <dbl>         <dbl>   <dbl>   <dbl>      <dbl>  <dbl> <dbl>
    ## 1     2     1             1       1    15.5          1   69.4  4.47
