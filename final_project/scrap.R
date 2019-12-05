library(tidyverse)

# variable names (OLD) ----
variables = rbind(
c("PINST", "School Name"),
c("PADDRS", "Location Address"),
c("PCITY", "Location City"),
c("PSTABB", "Location State"),
c("PZIP", "Location ZIP"),
# c("PL_ADD", "Location Address"),
# c("PL_CIT", "Location City"),
# c("PL_STABB", "Location State"),
# c("PL_ZIP", "Location ZIP"),
c("PPHONE", "School Phone Number"),
c("DIOCESE", "Diocese of Catholic school"),
c("HIGR2018", "Highest grade level in school"),
c("LEVEL", "Grade level of school"),
c("LATITUDE18", "Latitude"),
c("LOGR2018", "Lowest grade level in school"),
c("LONGITUDE18", "Longitude"),
c("MALES", "Number of K–12 and ungraded male students in the school"),
c("NUMSTUDS", "Number of K–12 and ungraded students in the school"),
c("NUMTEACH", "Number of Full-Time-Equivalent c(FTE) teachers in the school"),
c("ORIENT", "School’s religious or nonsectarian orientation"),
c("P_ASIAN", "Percentage of K–12 and ungraded students who are Asian, not of Hispanic or Latino origin"),
c("P_BLACK", "Percentage of K–12 and ungraded students who are Black or African American, not of Hispanic or Latino origin"),
c("P_HISP", "Percentage of K–12 and ungraded students who are Hispanic or Latino, regardless of race"),
c("P_INDIAN", "Percentage of K–12 and ungraded students who are American Indian or Alaska Native, not of Hispanic or Latino origin"),
c("P_PACIFIC", "Percentage of K–12 and ungraded students who are Native Hawaiian or other Pacific Islander, not of Hispanic or Latino origin"),
c("P_TR", "Percentage of K–12 and ungraded students who are Two or more races, not of Hispanic or Latino origin"),
c("P_WHITE", "Percentage of K–12 and ungraded students who are White, not of Hispanic or Latino origin"),
# c("REGION", "Geographic region of school"),
c("RELIG", "School’s religious affiliation"),
c("SIZE", "Categorized number of K–12 and ungraded students in the school"),
c("S_KG", "Total number of kindergarten students in the school"),
c("STTCH_RT", "Student/teacher ratio"),
c("TABFLAG", "Tabulation flag"),
c("TOTHRS", "Length of school day in hours"),
c("TYPOLOGY", "NCES 9-category typology"),
c("UCOMMTYP", "Urban-centric community type"),
c("ULOCALE18", "Urban-centric locale code")
) %>%
    data.frame
names(variables) = c("variable", "definition")

# variable names ----
library(openxlsx)
variable_layout = read.xlsx("final_project/Layout 2017-18 PU.xlsx") %>%
    filter(Name %in% c("PINST", "NUMSTUDS", "S_KG", "STTCH_RT", 
                       "ORIENT", "TYPOLOGY", "LEVEL", "TOTHRS", "UCOMMTYP", 
                       "LATITUDE18", "LONGITUDE18", "P_ASIAN", 
                       "P_BLACK", "P_HISP", "P_INDIAN", "P_PACIFIC", "P_TR", 
                       "P_WHITE","PADDRS", "PCITY", "PSTABB","PZIP", "PPHONE"
                     #, "ULOCALE18", "RELIG", "REGION", "MALES","LOGR2018", "HIGR2018", "SIZE", "DIOCESE","NUMTEAC"
                     )) %>%
    select(Name, Label)

# Variable codes and definitions ----
TYPOLOGY = 
rbind(c("1", "Catholic, parochial"),
c("2", "Catholic, diocesan"),
c("3", "Catholic, private"),
c("4", "Other Religious, Conservative Christian"),
c("5", "Other Religious, affiliated"),
c("6", "Other Religious, unaffiliated"),
c("7", "Nonsectarian, Regular"),
c("8", "Nonsectarian, special emphasis"),
c("9", "Nonsectarian, special education")
) %>%
    data.frame(stringsAsFactors = F)
names(TYPOLOGY) = c("TYPOLOGY", "TYPOLOGY_def")
TYPOLOGY[,1] = as.numeric(TYPOLOGY[,1])

UCOMMTYP = rbind(c("1", "City"),
c("2", "Suburb"),
c("3", "Town"),
c("4", "Rural "))%>%
    data.frame()
names(UCOMMTYP) = c("UCOMMTYP", "UCOMMTYP_def")
UCOMMTYP[,1] = as.numeric(UCOMMTYP[,1])

ORIENT= rbind(c("1", "Roman Catholic"),
c("2", "African Methodist Episcopal"),
c("3", "Amish"),
c("4", "Assembly of God"),
c("5", "Baptist"),
c("6", "Brethren"),
c("7", "Calvinist"),
c("8", "Christian, no specific denomination"),
c("10", "Church of God"),
c("11", "Church of God in Christ"),
c("12", "Church of the Nazarene"),
c("13", "Disciples of Christ"),
c("14", "Episcopal"),
c("15", "Friends"),
c("16", "Greek Orthodox"),
c("17", "Islamic"),
c("18", "Jewish"),
c("19", "Latter Day Saints"),
c("20", "Lutheran Church - Missouri Synod"),
c("21", "Evangelical Lutheran Church in America"),
c("24", "Mennonite"),
c("25", "Methodist"),
c("26", "Pentecostal"),
c("27", "Presbyterian"),
c("28", "Seventh-day Adventist"),
c("29", "Other"),
c("30", "Nonsectarian")) %>%
    data.frame()
names(ORIENT) = c("ORIENT", "ORIENT_def")
ORIENT[,1] = as.numeric(ORIENT[,1])

LEVEL = rbind(c("1", "Elementary"),
c("2", "Secondary"),
c("3", "Combined"))%>%
    data.frame()
names(LEVEL) = c("LEVEL", "LEVEL_def")
LEVEL[,1] = as.numeric(LEVEL[,1])

# loads data ----

df = read.csv("final_project/pss1718_pu.csv", stringsAsFactors = F) %>%
    select(c("PSTABB",as.character(variable_layout$Name))) %>%
    rename(lat = LATITUDE18,
           long = LONGITUDE18)

df = left_join(df, TYPOLOGY, by = "TYPOLOGY") %>%
    left_join(UCOMMTYP, by = "UCOMMTYP") %>%
    left_join(ORIENT, by = "ORIENT") %>%
    left_join(LEVEL, by = "LEVEL") %>%
    select(-c(TYPOLOGY, LEVEL, ORIENT, UCOMMTYP))

names(df) = gsub("_def","",names(df))
# county selection ----
selected_counties = c(#"24031", # Montgommery
                      "51510", # Alexandria
                      "51013", # Arlington
                      "51059", # Fairfax
                      "51600", # Fairfax City
                      "51610" # Falls Church
                      ) 
z2c = read.csv("final_project/uszips.csv", stringsAsFactors = F) %>%
    filter(county_fips %in% selected_counties)
z2c$zip

# This overwrites the mailing zip with the location zip if the mailing address and the location address are not the same.
df[(!is.na(df$PL_ZIP)), "PZIP"] = df[(!is.na(df$PL_ZIP)), "PL_ZIP"]
df = df %>%
    filter(PZIP %in% z2c$zip)

# makes popup ----
df = df %>%
    select(PINST, NUMSTUDS, S_KG, STTCH_RT, 
             ORIENT, TYPOLOGY, LEVEL, TOTHRS, UCOMMTYP, P_ASIAN, 
             P_BLACK, P_HISP, P_INDIAN, P_PACIFIC, P_TR, 
             P_WHITE,PADDRS, PCITY, PSTABB,PZIP, PPHONE, everything())
df$popup = ""
for(i in 1:nrow(df)){
    x = data.frame(t(df[i,] %>%
                         select(-lat, -long)
    ))
    names(x) = "data"
    x$Name = rownames(x)
    x = left_join(x, variable_layout, by = "Name")
    
    x = x[,c("Label", "Data")]
    
    df$popup[i] = knitr::kable(x, format = "html")
}


# plots map ----
library(leaflet)

# Show first 20 rows from the `quakes` dataset
leaflet(data = df) %>% 
    addTiles() %>%
    addCircles(~long, 
               ~lat,
               fillOpacity = 0.5,
               weight = 0.2,
               radius = ~as.numeric(NUMSTUDS),
               popup = ~as.character(popup), 
               label = ~as.character(PINST))

