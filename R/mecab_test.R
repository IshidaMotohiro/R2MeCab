#'Calcuate Frequency table
# 
#'This simple function calcuate Frequency table
#'@name mecab_test
#'@param str character
#'@return Data Frame
#'@keywords MeCab

mecab_test  <- function(str){
  if ((!is.character(str)) || nchar(str) < 1){
    stop ("arg must be characters")
  }else{
    .Call( "mecab_test", str, PACKAGE = "R2MeCab" )
  }
}

