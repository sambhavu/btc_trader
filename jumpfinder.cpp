#include<algorithm>
#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>

using namespace std; 

const int intsize = 200000;
const double twopi = 6.28318530718; 

double BTC[intsize];

class crypto{
    
    public:
    
    
    
    const double mgmntfee = .02;

    double t = intsize/(60.0*24.0);
    
 
    double intrate;
    double deposit; 
    double initial;
    double AUM;
    double leverage; 
    double debt;
    double intexpense; 
    double maxvolume;
    double mgmnt; 
    
    bool trading = true;
    
    
    crypto();
    
    double trader(int today, double v, double r);
    
    double perc_change(double prev, double today);
    
    void print_results(double assets);
    
};




crypto::crypto(){ 
    
    double balance_req;
    balance_req = 3000;
    
    
    cout<<"Initial Deposit Amount = "; 
    std::cin >> deposit; 
    
    cout<<"Leverage Ratio = "; 
    std::cin >> leverage; 
    
    cout<<"Interest Rate = "; 
    std::cin >> intrate; 
    intrate = intrate/365.0;
    
    
    /*
    deposit = 100000;
    leverage = 2;
    intrate = .06/365.0;
    */
    
 
 
    AUM         = deposit*leverage;
    debt        = AUM-deposit;
    mgmnt       = AUM*mgmntfee; 
    initial     = AUM-mgmnt;
    intexpense  = debt*intrate*t; 
    maxvolume   = initial/balance_req;
    
 
    if(initial<balance_req){
     
        trading = false;
        cout<<"ERROR\n\n **not enough capital**\n\n";
        cout<<"Minimum Capital Required = "<<balance_req; 
    }
    else{ 
        cout<<"Initial Deposit(USD)                         =  "<<deposit<<"\n";
        cout<<"Leverage Ratio                               =  "<<leverage<<"\n";
        cout<<"Daily Interest Rate on Borrowed Funds        =  "<<intrate*100<<"%\n";
        cout<<"________________________________________________\n";
        cout<<"Assets                                       =  "<<AUM<<"\n";
        cout<<"Less Managment Fee("<<mgmntfee*100<<"%)                       = -"<<mgmnt<<"\n";
        cout<<"________________________________________________\n";
        cout<<"Initial Capital Investment                   =  "<<initial<<"\n\n";
        cout<<"Expected Trading Volume                      =  "<<maxvolume<<"\n\n";
        
        
    }
}




void crypto :: print_results(double assets){
    
    
    cout<<"**Bitcoin Trading Complete**\n\nTrading Duration = "<<t<<" Days"<<"\n";
    
    
    double revenue; 
    double earnings; 
    double ret; 
    double profit; 

    
    revenue = assets;
    earnings = revenue-debt-intexpense; 

    
    
    cout<<"\n\n\n";
    
    cout<<"Liquidation of Assets Under Management(USD)  =  "<<revenue<<"\n";
    cout<<"Debt                                         = -"<<debt<<"\n";
    cout<<"________________________________________________\n";
    cout<<"Earnings Before Interest                     =  "<<revenue-debt<<"\n\n";
    cout<<"Interest Expense                             = -"<<intexpense<<"\n";
    cout<<"________________________________________________\n";
    cout<<"Earnings                                     =  "<<earnings<<"\n"; 

    cout<<"Management Fee Income                        = +"<<mgmnt<<"\n";
    cout<<"________________________________________________\n";
    cout<<"Total Management Income Generated            = "<<earnings+mgmnt<<"\n\n\n\n";
    
    ret = ((earnings-deposit)/deposit)*100;
    
    
    cout<<"\n\nFund Return("<<deposit<<"->"<<earnings<<") = "<<ret<<"%\n";
 
    
    
    
}










double crypto :: trader(int today,double v,double r){ 
    //strategy 
    
   double upper, lower;
   double spot =  BTC[today];
   upper=spot*1.1;
   lower=spot*.92;

   double jump=.05;
   double njump=-.05;
   int found=1;

   int p=today
   double change;

   while(found)
   { 
      change = (BTC[p]-BTC[p-1])/BTC[p-1]);
      if(change>jump)
       { 
             found=0;
             return 1;
       }
 
      if(change<njump)
      {
           found =0;
           return -1;
      } 
      p--;
}
} 

     
      

       
 
  
    

    
    
}











double crypto :: perc_change(double prev, double today){
    return (today-prev)/prev; 
}









int main(){
    
    crypto btc;
    
    std::ifstream infile;
    
    infile.open("/users/user/Desktop/text.txt", std::ifstream::binary);
    
    
    for(int d = 0; d<intsize; d++){
        infile >> BTC[d];
    }
 
    double position, pnl, dp, assets, accuracy, val, w, r; 
    vector<double> asset; 
    double rev = 1;
    assets = btc.initial;
    asset.push_back(assets);
    int checkr = 1.0;
 
    w=0; 
    r=0; 
 
    if(btc.trading){
        for(int i=1;i<intsize;i++)
        {
            position = btc.trader(i-1,btc.maxvolume,rev);
            
            
            
            
            
    
            if(position>=0){
                dp = btc.perc_change(BTC[i-1],BTC[i]) * position * BTC[i-1];
            }
            if(position<0){
                dp = btc.perc_change(BTC[i-1],BTC[i])*(position) * BTC[i-1]; 
            }
            
            if(dp>0){
                
                r = r+1.0;
            }
            if(dp<0){
                
                w=w+1.0;
            }
            
            
            
            
            checkr++; 
            assets = assets + dp;
            asset.push_back(assets);
            cout<<assets<<"\n";
            
            if(checkr%10000==0){
                if((asset[i]-asset[i-10000])>=0){
                    if(rev==1.0){
                        rev = 1.0;
                    }
                    else if(rev==-1.0){
                        rev = -1.0;
                    }
                }
                if((asset[i]-asset[i-10000])<0){
                    if(rev==1.0){
                        rev = -1.0;
                    }
                    else if(rev==-1.0){
                        rev = 1.0;
                    }
                }
                
            }//end flip
        }
    }
 
 
    if(btc.trading){
      btc.print_results(assets);
    }
    else{
      cout<<"\n\nBitcoin Trading Failed\n\n";
    }
    
 
 
 
    cout<<"Accuracy = "<<(r/(w+r))*100<<"%";
 
 
    
    return 0;   
}
