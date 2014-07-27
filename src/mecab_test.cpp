


 #include <Rcpp.h>
 #include "util.h"
 #include "setMap.h"
 #include "mecab_test.h"
 #include <list>
 #include "mecab.h"

 SEXP mecab_test (SEXP str){
  string input = Rcpp::as<string> (str);
  //MeCabの初期化
  mecab_t * mecab = mecab_new2("");
  if (!mecab) {return R_NilValue ;}else {
    const mecab_node_t * node = mecab_sparse_tonode(mecab, input.c_str());
    if (!node) {
      if (mecab) {
	 mecab_destroy (mecab);  // mecab = NULL;
	// free(mecab);
      }
      return R_NilValue ;
    } 

  //解析結果を保存するオブジェクト
  vector <string> feat; 
  map <string, int> m;
 
  //解析結果を取り出す
  for (; node; node = node->next){
    if (node->stat == MECAB_BOS_NODE) Rprintf ("\n");
    else if (node->stat == MECAB_EOS_NODE) Rprintf ("\n");
    else {
      std::string buf1 (node->surface, node->length) ;
      if (buf1.size () > 0){
         feat = tmpsplit (string (node->feature), ",");
         buf1  = buf1 + "-" + feat[0];
         setMap (m, buf1);
      }else {
         continue;
      }
    }
  }
 
  mecab_destroy (mecab); 
    if (m.size () > 0){
      Rcpp::DataFrame res = Rcpp::DataFrame::create(Rcpp::_["FREQ"] = m); 
      return res;
    }else{
     return R_NilValue;
    }
   }
 }
