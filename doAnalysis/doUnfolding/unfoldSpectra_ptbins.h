const int NETABINS=4;

//these are the binnings from raghav's NLO files. they impose a minimum of 56 GeV (current lower limit of data) and cut off the large high pt bin (686-1000 GeV)
std::vector<std::vector<double>> SMP_ptbins{

/*   {//00eta05  OLD BINS before 10/14/2020
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.,      638.,      686.,
737., 790., 846., 905., 967. },
  {//05eta10
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.,      638.,      686.,  
      737.,      790.,      846.,      905.,      967. },
  {//10eta15
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.,      638.,      686.,  
      737.,      790.,      846.,      905.,      967. },
  {//15eta20
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.,      638.,      686.,  
      737.,      790.,      846.,      905.,      967. }
}; */

//NEW BINS after 10/14/2020:
{//00eta05
    56.,    64.,    74.,       84.,       97.,       
	 114.,  133.,  153.,      174.,      196.,
	 220.,  245.,  272.,      300.,      330.,
	 395.,  507.,  638.,      846. },
  {//05eta10
     56.,     64.,       74.,        84.,        97.,       
	114.,  133.,      153.,      174.,      196.,
	220.,  245.,      272.,      300.,      330.,
	395.,  507.,      638.,      846.
 },
  {//10eta15
     56.,     64.,       74.,       84.,        97.,     
	114.,   133.,    153.,     174.,      196.,
	220.,   245.,    272.,     330.,      395.,
	507.,     638. },
  {//15eta20
	56.,     64.,        74.,        84.,       97.,      
	 114.,  133.,      153.,      174.,      196., 
	 220.,  245.,      272.,      330.,      395.,
	 507. }
};


std::vector<std::vector<double>> NLO_SMP_ptbins{
  {//00eta05
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.,      638.,      686.  },
  {//05eta10
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.,      638.,      686.  },
  {//10eta15
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.,      548.,      592.	        },
  {//15eta20
    56.,      64.,      74.,      84.,      97.,      114.,
      133.,      153.,      174.,      196.,      220.,      245.,
      272.,      300.,      330.,      362.,      395.,      430.,
      468.,      507.       }
};


std::vector<std::vector<double>> john_ptbins{
  {//00eta05
  56., 64.,  84.,  114.,
  153.,  196.,  245.,  300.,
  362.,  430.,  507.,  592.,
  686.,  790.,  905.,  1101.
},
  {//05eta10
  56., 64.,  84.,  114.,
  153.,  196.,  245.,  300.,
  362.,  430.,  507.,  592.,
  686.,  790.,  905.,  1101.
},
  {//10eta15
  56., 64.,  84.,  114.,
  153.,  196.,  245.,  300.,
  362.,  430.,  507.,  592.,
  686.,  790.,  905.,  1101.
},
  {//15eta20
  56., 64.,  84.,  114.,
  153.,  196.,  245.,  300.,
  362.,  430.,  507.,  592.,
  686.,  790.,  905.,  1101.
}
};


//chris binning
std::vector<std::vector<double>> chris_ptbins{
  {//00eta05    // 20.,// 30.,// 40.,// 50.,
    60.,70.,80.,90.,100.,110.,
      120.,130.,140.,150.,160.,170.,
      180.,190.,200.,210.,220.,230.,
      240.,250.,260.,270.,280.,290.,
      310.,330.,350.,370.,400.,430.,
      500.//,//1500.,
  },  
  {//05eta10    // 20.,// 30.,// 40.,// 50.,
    60.,70.,80.,90.,100.,110.,
      120.,130.,140.,150.,160.,170.,
      180.,190.,200.,210.,220.,230.,
      240.,250.,260.,270.,280.,290.,
      310.,330.,350.,370.,400.,430.,
      500.//,//1500.,
  },
  {//10eta15    // 20.,// 30.,// 40.,// 50.,
    60.,70.,80.,90.,100.,110.,
      120.,130.,140.,150.,160.,170.,
      180.,190.,200.,210.,220.,230.,
      240.,250.,260.,270.,280.,290.,
      310.,330.,350.,370.,400.,430.,
      500.//,      //1500.,
  },
  {//15eta20    // 20.,// 30.,// 40.,// 50.,
    60.,70.,80.,90.,100.,110.,
      120.,130.,140.,150.,160.,170.,
      180.,190.,200.,210.,220.,230.,
      240.,250.,260.,270.,280.,290.,
      310.,330.,350.,370.,400.,430.,
      500.//,//1500.,  
  }
};






//// ------ SMP SPECTRA BINS ORIGINAL ------
//// ------ DO NOT TOUCH ------
//const double anabins_pt_SMP[] = {
//  1, 5, 6, 8, 10, 12, 15, 18, 21, 24, 28, 
//  32, 37, 43, 49, 
//  56, 64, 74, 84,97, 114, 
//  133, 153, 174, 196, 220, 
//  245, 272, 300,   330, 
//  362, 395, 430, 
//  468,  507, 
//  548, 592, 638, 
//  686, 
//  737, 790, 846,  905,   967,  1032, 
//  1101, 1172, 1248, 1327, 
//  //1410, 1497, 1588, 1684, 1784, 1890, 2000,
//  //2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 
//  //4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000
//  };

