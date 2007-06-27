// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:

#include "config.h"
#include "../quadraturerules.hh"

namespace Dune {

  //!
  template<int dim>
  class SimplexQuadraturePoints;

  /** Singleton holding the Gauss points on the interval */
  template<int dim>
  struct SimplexQuadraturePointsSingleton {
    static SimplexQuadraturePoints<dim> sqp;
  };

  template<>
  struct SimplexQuadraturePointsSingleton<2> {
    static SimplexQuadraturePoints<2> sqp;
  };

  template<>
  struct SimplexQuadraturePointsSingleton<3> {
    static SimplexQuadraturePoints<3> sqp;
  };

  template<>
  class SimplexQuadraturePoints<2>
  {
  public:
    enum { MAXP=33};
    enum { highest_order=12 };

    //! initialize quadrature points on the interval for all orders
    SimplexQuadraturePoints ()
    {
      int m = 0;
      O[m] = 0;

      // polynom degree 1
      m = 1;
      G[m][0][0] = 0.333333333333333333333333333333333;
      G[m][0][1] = 0.333333333333333333333333333333333;
      W[m][0] = 0.5;
      O[m] = 1;

      // polynom degree 2
      // symmetric
      m = 3;
      G[m][0][0] = 4.0/6.0;
      G[m][0][1] = 1.0/6.0;
      G[m][1][0] = 1.0/6.0;
      G[m][1][1] = 4.0/6.0;
      G[m][2][0] = 1.0/6.0;
      G[m][2][1] = 1.0/6.0;
      W[m][0] = 0.5/3.0;
      W[m][1] = 0.5/3.0;
      W[m][2] = 0.5/3.0;
      O[m] = 2;

      // polynom degree 3
      // symmetric
      m = 4;
      G[m][0][0] = 10.0/30.0;
      G[m][0][1] = 10.0/30.0;
      G[m][1][0] = 18.0/30.0;
      G[m][1][1] = 6.0/30.0;
      G[m][2][0] = 6.0/30.0;
      G[m][2][1] = 18.0/30.0;
      G[m][3][0] = 6.0/30.0;
      G[m][3][1] = 6.0/30.0;

      W[m][0] = 0.5 * -27.0/48.0;
      W[m][1] = 0.5 * 25.0/48.0;
      W[m][2] = 0.5 * 25.0/48.0;
      W[m][3] = 0.5 * 25.0/48.0;
      O[m] = 3;

      // polynomial degree 4
      // symmetric points
      m = 6;
      G[m][0][0] = 0.81684757298045851308085707319560;
      G[m][0][1] = 0.091576213509770743459571463402202;
      G[m][1][0] = 0.091576213509770743459571463402202;
      G[m][1][1] = 0.81684757298045851308085707319560;
      G[m][2][0] = 0.091576213509770743459571463402202;
      G[m][2][1] = 0.091576213509770743459571463402202;
      G[m][3][0] = 0.10810301816807022736334149223390;
      G[m][3][1] = 0.44594849091596488631832925388305;
      G[m][4][0] = 0.44594849091596488631832925388305;
      G[m][4][1] = 0.10810301816807022736334149223390;
      G[m][5][0] = 0.44594849091596488631832925388305;
      G[m][5][1] = 0.44594849091596488631832925388305;

      W[m][0] = 0.5 * 0.10995174365532186763832632490021;
      W[m][1] = 0.5 * 0.10995174365532186763832632490021;
      W[m][2] = 0.5 * 0.10995174365532186763832632490021;
      W[m][3] = 0.5 * 0.22338158967801146569500700843312;
      W[m][4] = 0.5 * 0.22338158967801146569500700843312;
      W[m][5] = 0.5 * 0.22338158967801146569500700843312;
      O[m] = 4;

      // polynomial degree 5
      // symmetric points

      m = 7;
      G[m][0][0] = 0.333333333333333333333333333333333;
      G[m][0][1] = 0.333333333333333333333333333333333;
      G[m][1][0] = 0.79742698535308732239802527616975;
      G[m][1][1] = 0.1012865073234563388009873619151;
      G[m][2][0] = 0.10128650732345633880098736191512;
      G[m][2][1] = 0.79742698535308732239802527616975;
      G[m][3][0] = 0.10128650732345633880098736191512;
      G[m][3][1] = 0.10128650732345633880098736191512;
      G[m][4][0] = 0.05971587178976982045911758097311;
      G[m][4][1] = 0.47014206410511508977044120951345;
      G[m][5][0] = 0.47014206410511508977044120951345;
      G[m][5][1] = 0.05971587178976982045911758097311;
      G[m][6][0] = 0.47014206410511508977044120951345;
      G[m][6][1] = 0.47014206410511508977044120951345;

      W[m][0] = 0.5 * 0.225;
      W[m][1] = 0.5 * 0.12593918054482715259568394550018;
      W[m][2] = 0.5 * 0.12593918054482715259568394550018;
      W[m][3] = 0.5 * 0.12593918054482715259568394550018;
      W[m][4] = 0.5 * 0.13239415278850618073764938783315;
      W[m][5] = 0.5 * 0.13239415278850618073764938783315;
      W[m][6] = 0.5 * 0.13239415278850618073764938783315;
      O[m] = 5;

      // polynomial degree 6
      /* 12 inner Gauss points, positive weights */
      m=12;
      G[m][0][0] = 0.063089014491502228340331602870819;
      G[m][0][1] = 0.063089014491502228340331602870819;
      G[m][1][0] = 0.063089014491502228340331602870819;
      G[m][1][1] = 0.87382197101699554331933679425836;
      G[m][2][0] = 0.87382197101699554331933679425836;
      G[m][2][1] = 0.063089014491502228340331602870819;
      G[m][3][0] = 0.24928674517091042129163855310702;
      G[m][3][1] = 0.24928674517091042129163855310702;
      G[m][4][0] = 0.24928674517091042129163855310702;
      G[m][4][1] = 0.50142650965817915741672289378596;
      G[m][5][0] = 0.50142650965817915741672289378596;
      G[m][5][1] = 0.24928674517091042129163855310702;
      G[m][6][0] = 0.053145049844816947353249671631398;
      G[m][6][1] = 0.31035245103378440541660773395655;
      G[m][7][0] = 0.053145049844816947353249671631398;
      G[m][7][1] = 0.63650249912139864723014259441205;
      G[m][8][0] = 0.31035245103378440541660773395655;
      G[m][8][1] = 0.053145049844816947353249671631398;
      G[m][9][0] = 0.31035245103378440541660773395655;
      G[m][9][1] = 0.63650249912139864723014259441205;
      G[m][10][0] = 0.63650249912139864723014259441205;
      G[m][10][1] = 0.053145049844816947353249671631398;
      G[m][11][0] = 0.63650249912139864723014259441205;
      G[m][11][1] = 0.31035245103378440541660773395655;

      W[m][0] = 0.5 * 0.050844906370206816920936809106869;
      W[m][1] = 0.5 * 0.050844906370206816920936809106869;
      W[m][2] = 0.5 * 0.050844906370206816920936809106869;
      W[m][3] = 0.5 * 0.11678627572637936602528961138558;
      W[m][4] = 0.5 * 0.11678627572637936602528961138558;
      W[m][5] = 0.5 * 0.11678627572637936602528961138558;
      W[m][6] = 0.5 * 0.082851075618373575193553456420442;
      W[m][7] = 0.5 * 0.082851075618373575193553456420442;
      W[m][8] = 0.5 * 0.082851075618373575193553456420442;
      W[m][9] = 0.5 * 0.082851075618373575193553456420442;
      W[m][10] = 0.5 * 0.082851075618373575193553456420442;
      W[m][11] = 0.5 * 0.082851075618373575193553456420442;
      O[m] = 6;

      // polynomial degree 7
      /* 12 inner Gauss points, positive weights */
      m=12;
      G[m][0][0] = 0.0623822650944021181736830009963499;
      G[m][0][1] = 0.0675178670739160854425571310508685;
      G[m][1][0] = 0.0675178670739160854425571310508685;
      G[m][1][1] = 0.870099867831681796383759867952782;
      G[m][2][0] = 0.870099867831681796383759867952782;
      G[m][2][1] = 0.0623822650944021181736830009963499;
      G[m][3][0] = 0.0552254566569266117374791902756449;
      G[m][3][1] = 0.321502493851981822666307849199202;
      G[m][4][0] = 0.321502493851981822666307849199202;
      G[m][4][1] = 0.623272049491091565596212960525153;
      G[m][5][0] = 0.623272049491091565596212960525153;
      G[m][5][1] = 0.0552254566569266117374791902756449;
      G[m][6][0] = 0.0343243029450971464696306424839376;
      G[m][6][1] = 0.660949196186735657611980310197799;
      G[m][7][0] = 0.660949196186735657611980310197799;
      G[m][7][1] = 0.304726500868167195918389047318263;
      G[m][8][0] = 0.304726500868167195918389047318263;
      G[m][8][1] = 0.0343243029450971464696306424839376;
      G[m][9][0] = 0.515842334353591779257463386826430;
      G[m][9][1] = 0.277716166976391782569581871393723;
      G[m][10][0] = 0.277716166976391782569581871393723;
      G[m][10][1] = 0.20644149867001643817295474177985;
      G[m][11][0] = 0.20644149867001643817295474177985;
      G[m][11][1] = 0.515842334353591779257463386826430;

      W[m][0] = 0.5 * 0.053034056314872502857508360921478;
      W[m][1] = 0.5 * 0.053034056314872502857508360921478;
      W[m][2] = 0.5 * 0.053034056314872502857508360921478;
      W[m][3] = 0.5 * 0.087762817428892110073539806278575;
      W[m][4] = 0.5 * 0.087762817428892110073539806278575;
      W[m][5] = 0.5 * 0.087762817428892110073539806278575;
      W[m][6] = 0.5 * 0.057550085569963171476890993800437;
      W[m][7] = 0.5 * 0.057550085569963171476890993800437;
      W[m][8] = 0.5 * 0.057550085569963171476890993800437;
      W[m][9] = 0.5 * 0.13498637401960554892539417233284;
      W[m][10] = 0.5 * 0.13498637401960554892539417233284;
      W[m][11] = 0.5 * 0.13498637401960554892539417233284;
      O[m] = 7;

      // polynomial degree 8
      /* 16 inner Gauss points, positive weights */

      m=16;
      G[m][0][0] = 0.33333333333333333333333333333333;
      G[m][0][1] = 0.33333333333333333333333333333333;
      G[m][1][0] = 0.17056930775176020662229350149146;
      G[m][1][1] = 0.17056930775176020662229350149146;
      G[m][2][0] = 0.17056930775176020662229350149146;
      G[m][2][1] = 0.65886138449647958675541299701707;
      G[m][3][0] = 0.65886138449647958675541299701707;
      G[m][3][1] = 0.17056930775176020662229350149146;
      G[m][4][0] = 0.050547228317030975458423550596599;
      G[m][4][1] = 0.050547228317030975458423550596599;
      G[m][5][0] = 0.050547228317030975458423550596599;
      G[m][5][1] = 0.89890554336593804908315289880680;
      G[m][6][0] = 0.89890554336593804908315289880680;
      G[m][6][1] = 0.050547228317030975458423550596599;
      G[m][7][0] = 0.45929258829272315602881551449417;
      G[m][7][1] = 0.45929258829272315602881551449417;
      G[m][8][0] = 0.45929258829272315602881551449417;
      G[m][8][1] = 0.08141482341455368794236897101166;
      G[m][9][0] = 0.08141482341455368794236897101166;
      G[m][9][1] = 0.45929258829272315602881551449417;
      G[m][10][0] = 0.72849239295540428124100037917606;
      G[m][10][1] = 0.26311282963463811342178578628464;
      G[m][11][0] = 0.72849239295540428124100037917606;
      G[m][11][1] = 0.00839477740995760533721383453930;
      G[m][12][0] = 0.26311282963463811342178578628464;
      G[m][12][1] = 0.72849239295540428124100037917606;
      G[m][13][0] = 0.26311282963463811342178578628464;
      G[m][13][1] = 0.00839477740995760533721383453930;
      G[m][14][0] = 0.00839477740995760533721383453930;
      G[m][14][1] = 0.72849239295540428124100037917606;
      G[m][15][0] = 0.00839477740995760533721383453930;
      G[m][15][1] = 0.26311282963463811342178578628464;

      W[m][0] = 0.5 * 0.14431560767778716825109111048906;
      W[m][1] = 0.5 * 0.10321737053471825028179155029213;
      W[m][2] = 0.5 * 0.10321737053471825028179155029213;
      W[m][3] = 0.5 * 0.10321737053471825028179155029213;
      W[m][4] = 0.5 * 0.032458497623198080310925928341780;
      W[m][5] = 0.5 * 0.032458497623198080310925928341780;
      W[m][6] = 0.5 * 0.032458497623198080310925928341780;
      W[m][7] = 0.5 * 0.095091634267284624793896104388584;
      W[m][8] = 0.5 * 0.095091634267284624793896104388584;
      W[m][9] = 0.5 * 0.095091634267284624793896104388584;
      W[m][10] = 0.5 * 0.027230314174434994264844690073909;
      W[m][11] = 0.5 * 0.027230314174434994264844690073909;
      W[m][12] = 0.5 * 0.027230314174434994264844690073909;
      W[m][13] = 0.5 * 0.027230314174434994264844690073909;
      W[m][14] = 0.5 * 0.027230314174434994264844690073909;
      W[m][15] = 0.5 * 0.027230314174434994264844690073909;
      O[m] = 8;

      // polynomial degree 9
      /* 19 inner Gauss points, positive weights */

      m=19;
      G[m][0][0] = 0.333333333333333333333333333333333;
      G[m][0][1] = 0.333333333333333333333333333333333;
      G[m][1][0] = 0.48968251919873762778370692483619;
      G[m][1][1] = 0.48968251919873762778370692483619;
      G[m][2][0] = 0.48968251919873762778370692483619;
      G[m][2][1] = 0.02063496160252474443258615032762;
      G[m][3][0] = 0.02063496160252474443258615032762;
      G[m][3][1] = 0.48968251919873762778370692483619;
      G[m][4][0] = 0.43708959149293663726993036443535;
      G[m][4][1] = 0.43708959149293663726993036443535;
      G[m][5][0] = 0.43708959149293663726993036443535;
      G[m][5][1] = 0.12582081701412672546013927112929;
      G[m][6][0] = 0.12582081701412672546013927112929;
      G[m][6][1] = 0.43708959149293663726993036443535;
      G[m][7][0] = 0.18820353561903273024096128046733;
      G[m][7][1] = 0.18820353561903273024096128046733;
      G[m][8][0] = 0.18820353561903273024096128046733;
      G[m][8][1] = 0.62359292876193453951807743906533;
      G[m][9][0] = 0.62359292876193453951807743906533;
      G[m][9][1] = 0.18820353561903273024096128046733;
      G[m][10][0] = 0.044729513394452709865106589966276;
      G[m][10][1] = 0.044729513394452709865106589966276;
      G[m][11][0] = 0.044729513394452709865106589966276;
      G[m][11][1] = 0.91054097321109458026978682006745;
      G[m][12][0] = 0.91054097321109458026978682006745;
      G[m][12][1] = 0.044729513394452709865106589966276;
      G[m][13][0] = 0.74119859878449802069007987352342;
      G[m][13][1] = 0.036838412054736283634817598783385;
      G[m][14][0] = 0.74119859878449802069007987352342;
      G[m][14][1] = 0.22196298916076569567510252769319;
      G[m][15][0] = 0.036838412054736283634817598783385;
      G[m][15][1] = 0.74119859878449802069007987352342;
      G[m][16][0] = 0.036838412054736283634817598783385;
      G[m][16][1] = 0.22196298916076569567510252769319;
      G[m][17][0] = 0.22196298916076569567510252769319;
      G[m][17][1] = 0.74119859878449802069007987352342;
      G[m][18][0] = 0.22196298916076569567510252769319;
      G[m][18][1] = 0.036838412054736283634817598783385;

      W[m][0] = 0.5 * 0.097135796282798833819241982507289;
      W[m][1] = 0.5 * 0.031334700227139070536854831287209;
      W[m][2] = 0.5 * 0.031334700227139070536854831287209;
      W[m][3] = 0.5 * 0.031334700227139070536854831287209;
      W[m][4] = 0.5 * 0.077827541004774279316739356299404;
      W[m][5] = 0.5 * 0.077827541004774279316739356299404;
      W[m][6] = 0.5 * 0.077827541004774279316739356299404;
      W[m][7] = 0.5 * 0.079647738927210253032891774264045;
      W[m][8] = 0.5 * 0.079647738927210253032891774264045;
      W[m][9] = 0.5 * 0.079647738927210253032891774264045;
      W[m][10] = 0.5 * 0.025577675658698031261678798559000;
      W[m][11] = 0.5 * 0.025577675658698031261678798559000;
      W[m][12] = 0.5 * 0.025577675658698031261678798559000;
      W[m][13] = 0.5 * 0.043283539377289377289377289377289;
      W[m][14] = 0.5 * 0.043283539377289377289377289377289;
      W[m][15] = 0.5 * 0.043283539377289377289377289377289;
      W[m][16] = 0.5 * 0.043283539377289377289377289377289;
      W[m][17] = 0.5 * 0.043283539377289377289377289377289;
      W[m][18] = 0.5 * 0.043283539377289377289377289377289;
      O[m] = 9;

      // polynomial degree 10
      /* 25 inner Gauss points, positive weights */
      m= 25;
      G[m][0][0] = 0.333333333333333333333333333333333;
      G[m][0][1] = 0.333333333333333333333333333333333;
      G[m][1][0] = 0.42508621060209057296952951163804;
      G[m][1][1] = 0.42508621060209057296952951163804;
      G[m][2][0] = 0.42508621060209057296952951163804;
      G[m][2][1] = 0.14982757879581885406094097672391;
      G[m][3][0] = 0.14982757879581885406094097672391;
      G[m][3][1] = 0.42508621060209057296952951163804;
      G[m][4][0] = 0.023308867510000190714466386895980;
      G[m][4][1] = 0.023308867510000190714466386895980;
      G[m][5][0] = 0.023308867510000190714466386895980;
      G[m][5][1] = 0.95338226497999961857106722620804;
      G[m][6][0] = 0.95338226497999961857106722620804;
      G[m][6][1] = 0.023308867510000190714466386895980;
      G[m][7][0] = 0.62830740021349255642083766607883;
      G[m][7][1] = 0.22376697357697300622568649026820;
      G[m][8][0] = 0.62830740021349255642083766607883;
      G[m][8][1] = 0.14792562620953443735347584365296;
      G[m][9][0] = 0.22376697357697300622568649026820;
      G[m][9][1] = 0.62830740021349255642083766607883;
      G[m][10][0] = 0.22376697357697300622568649026820;
      G[m][10][1] = 0.14792562620953443735347584365296;
      G[m][11][0] = 0.14792562620953443735347584365296;
      G[m][11][1] = 0.62830740021349255642083766607883;
      G[m][12][0] = 0.14792562620953443735347584365296;
      G[m][12][1] = 0.22376697357697300622568649026820;
      G[m][13][0] = 0.61131382618139764891875500225390;
      G[m][13][1] = 0.35874014186443146457815530072385;
      G[m][14][0] = 0.61131382618139764891875500225390;
      G[m][14][1] = 0.02994603195417088650308969702225;
      G[m][15][0] = 0.35874014186443146457815530072385;
      G[m][15][1] = 0.61131382618139764891875500225390;
      G[m][16][0] = 0.35874014186443146457815530072385;
      G[m][16][1] = 0.02994603195417088650308969702225;
      G[m][17][0] = 0.02994603195417088650308969702225;
      G[m][17][1] = 0.61131382618139764891875500225390;
      G[m][18][0] = 0.02994603195417088650308969702225;
      G[m][18][1] = 0.35874014186443146457815530072385;
      G[m][19][0] = 0.82107206998562937337354441347218;
      G[m][19][1] = 0.14329537042686714530585663061732;
      G[m][20][0] = 0.82107206998562937337354441347218;
      G[m][20][1] = 0.03563255958750348132059895591050;
      G[m][21][0] = 0.14329537042686714530585663061732;
      G[m][21][1] = 0.82107206998562937337354441347218;
      G[m][22][0] = 0.14329537042686714530585663061732;
      G[m][22][1] = 0.03563255958750348132059895591050;
      G[m][23][0] = 0.03563255958750348132059895591050;
      G[m][23][1] = 0.82107206998562937337354441347218;
      G[m][24][0] = 0.03563255958750348132059895591050;
      G[m][24][1] = 0.14329537042686714530585663061732;

      W[m][0] = 0.5 * 0.079894504741239707831247045213386;
      W[m][1] = 0.5 * 0.071123802232377334639291287398658;
      W[m][2] = 0.5 * 0.071123802232377334639291287398658;
      W[m][3] = 0.5 * 0.071123802232377334639291287398658;
      W[m][4] = 0.5 * 0.0082238186904641955186466203624719;
      W[m][5] = 0.5 * 0.0082238186904641955186466203624719;
      W[m][6] = 0.5 * 0.0082238186904641955186466203624719;
      W[m][7] = 0.5 * 0.045430592296170018007073629243933;
      W[m][8] = 0.5 * 0.045430592296170018007073629243933;
      W[m][9] = 0.5 * 0.045430592296170018007073629243933;
      W[m][10] = 0.5 * 0.045430592296170018007073629243933;
      W[m][11] = 0.5 * 0.045430592296170018007073629243933;
      W[m][12] = 0.5 * 0.045430592296170018007073629243933;
      W[m][13] = 0.5 * 0.037359856234305276826236499001975;
      W[m][14] = 0.5 * 0.037359856234305276826236499001975;
      W[m][15] = 0.5 * 0.037359856234305276826236499001975;
      W[m][16] = 0.5 * 0.037359856234305276826236499001975;
      W[m][17] = 0.5 * 0.037359856234305276826236499001975;
      W[m][18] = 0.5 * 0.037359856234305276826236499001975;
      W[m][19] = 0.5 * 0.030886656884563988782513077004629;
      W[m][20] = 0.5 * 0.030886656884563988782513077004629;
      W[m][21] = 0.5 * 0.030886656884563988782513077004629;
      W[m][22] = 0.5 * 0.030886656884563988782513077004629;
      W[m][23] = 0.5 * 0.030886656884563988782513077004629;
      W[m][24] = 0.5 * 0.030886656884563988782513077004629;
      O[m] = 10;

      // polynomial degree 11
      /* 28 inner Gauss points, positive weights */

      m=28;
      G[m][0][0] = 0.858870281282636704039173938058347;
      G[m][0][1] = 0.141129718717363295960826061941652;
      G[m][1][0] = 0.858870281282636704039173938058347;
      G[m][1][1] = 0.0;
      G[m][2][0] = 0.141129718717363295960826061941652;
      G[m][2][1] = 0.858870281282636704039173938058347;
      G[m][3][0] = 0.141129718717363295960826061941652;
      G[m][3][1] = 0.0;
      G[m][4][0] = 0.0;
      G[m][4][1] = 0.858870281282636704039173938058347;
      G[m][5][0] = 0.0;
      G[m][5][1] = 0.141129718717363295960826061941652;
      G[m][6][0] = 0.333333333333333333333333333333333;
      G[m][6][1] = 0.333333333333333333333333333333333;
      G[m][7][0] = 0.025989140928287395260032485498841;
      G[m][7][1] = 0.025989140928287395260032485498841;
      G[m][8][0] = 0.025989140928287395260032485498841;
      G[m][8][1] = 0.94802171814342520947993502900232;
      G[m][9][0] = 0.94802171814342520947993502900232;
      G[m][9][1] = 0.025989140928287395260032485498841;
      G[m][10][0] = 0.094287502647922495630569776275405;
      G[m][10][1] = 0.094287502647922495630569776275405;
      G[m][11][0] = 0.094287502647922495630569776275405;
      G[m][11][1] = 0.81142499470415500873886044744919;
      G[m][12][0] = 0.81142499470415500873886044744919;
      G[m][12][1] = 0.094287502647922495630569776275405;
      G[m][13][0] = 0.49463677501721381374163260230644;
      G[m][13][1] = 0.49463677501721381374163260230644;
      G[m][14][0] = 0.49463677501721381374163260230644;
      G[m][14][1] = 0.01072644996557237251673479538713;
      G[m][15][0] = 0.01072644996557237251673479538713;
      G[m][15][1] = 0.49463677501721381374163260230644;
      G[m][16][0] = 0.20734338261451133345293402411297;
      G[m][16][1] = 0.20734338261451133345293402411297;
      G[m][17][0] = 0.20734338261451133345293402411297;
      G[m][17][1] = 0.58531323477097733309413195177407;
      G[m][18][0] = 0.58531323477097733309413195177407;
      G[m][18][1] = 0.20734338261451133345293402411297;
      G[m][19][0] = 0.43890780570049209506106538163613;
      G[m][19][1] = 0.43890780570049209506106538163613;
      G[m][20][0] = 0.43890780570049209506106538163613;
      G[m][20][1] = 0.12218438859901580987786923672775;
      G[m][21][0] = 0.12218438859901580987786923672775;
      G[m][21][1] = 0.43890780570049209506106538163613;
      G[m][22][0] = 0.67793765488259040154212614118875;
      G[m][22][1] = 0.044841677589130443309052391468801;
      G[m][23][0] = 0.67793765488259040154212614118875;
      G[m][23][1] = 0.27722066752827915514882146734245;
      G[m][24][0] = 0.044841677589130443309052391468801;
      G[m][24][1] = 0.67793765488259040154212614118875;
      G[m][25][0] = 0.044841677589130443309052391468801;
      G[m][25][1] = 0.27722066752827915514882146734245;
      G[m][26][0] = 0.27722066752827915514882146734245;
      G[m][26][1] = 0.67793765488259040154212614118875;
      G[m][27][0] = 0.27722066752827915514882146734245;
      G[m][27][1] = 0.044841677589130443309052391468801;

      W[m][0] = 0.5 * 0.0073623837833005542642588950473806;
      W[m][1] = 0.5 * 0.0073623837833005542642588950473806;
      W[m][2] = 0.5 * 0.0073623837833005542642588950473806;

      W[m][3] = 0.5 * 0.0073623837833005542642588950473806;
      W[m][4] = 0.5 * 0.0073623837833005542642588950473806;
      W[m][5] = 0.5 * 0.0073623837833005542642588950473806;

      W[m][6] = 0.5 * 0.087977301162232238798093169321456;
      W[m][7] = 0.5 * 0.0087443115537360230495164287998252;
      W[m][8] = 0.5 * 0.0087443115537360230495164287998252;
      W[m][9] = 0.5 * 0.0087443115537360230495164287998252;

      W[m][10] = 0.5 * 0.038081571993934937515024339435614;
      W[m][11] = 0.5 * 0.038081571993934937515024339435614;
      W[m][12] = 0.5 * 0.038081571993934937515024339435614;

      W[m][13] = 0.5 * 0.018855448056131292058476782591115;
      W[m][14] = 0.5 * 0.018855448056131292058476782591115;
      W[m][15] = 0.5 * 0.018855448056131292058476782591115;

      W[m][16] = 0.5 * 0.072159697544739526124029988586463;
      W[m][17] = 0.5 * 0.072159697544739526124029988586463;
      W[m][18] = 0.5 * 0.072159697544739526124029988586463;

      W[m][19] = 0.5 * 0.069329138705535899841765650903814;
      W[m][20] = 0.5 * 0.069329138705535899841765650903814;
      W[m][21] = 0.5 * 0.069329138705535899841765650903814;

      W[m][22] = 0.5 * 0.041056315429288566641652314907294;
      W[m][23] = 0.5 * 0.041056315429288566641652314907294;
      W[m][24] = 0.5 * 0.041056315429288566641652314907294;

      W[m][25] = 0.5 * 0.041056315429288566641652314907294;
      W[m][26] = 0.5 * 0.041056315429288566641652314907294;
      W[m][27] = 0.5 * 0.041056315429288566641652314907294;
      O[m] = 11;

      // polynomial degree 12
      /* 33 inner Gauss points, positive weights */
      m=33;
      G[m][0][0] = 0.02356522045239;
      G[m][0][1] = 0.488217389773805;
      G[m][1][0] = 0.488217389773805;
      G[m][1][1] = 0.02356522045239;
      G[m][2][0] = 0.488217389773805;
      G[m][2][1] = 0.488217389773805;
      G[m][3][0] = 0.43972439229446;
      G[m][3][1] = 0.43972439229446;
      G[m][4][0] = 0.43972439229446;
      G[m][4][1] = 0.120551215411079;
      G[m][5][0] = 0.120551215411079;
      G[m][5][1] = 0.43972439229446;
      G[m][6][0] = 0.271210385012116;
      G[m][6][1] = 0.271210385012116;
      G[m][7][0] = 0.271210385012116;
      G[m][7][1] = 0.457579229975768;
      G[m][8][0] = 0.457579229975768;
      G[m][8][1] = 0.271210385012116;
      G[m][9][0] = 0.127576145541586;
      G[m][9][1] = 0.127576145541586;
      G[m][10][0] = 0.127576145541586;
      G[m][10][1] = 0.7448477089168279;
      G[m][11][0] = 0.7448477089168279;
      G[m][11][1] = 0.127576145541586;
      G[m][12][0] = 0.02131735045321;
      G[m][12][1] = 0.02131735045321;
      G[m][13][0] = 0.02131735045321;
      G[m][13][1] = 0.9573652990935799;
      G[m][14][0] = 0.9573652990935799;
      G[m][14][1] = 0.02131735045321;
      G[m][15][0] = 0.115343494534698;
      G[m][15][1] = 0.275713269685514;
      G[m][16][0] = 0.115343494534698;
      G[m][16][1] = 0.6089432357797879;
      G[m][17][0] = 0.275713269685514;
      G[m][17][1] = 0.115343494534698;
      G[m][18][0] = 0.275713269685514;
      G[m][18][1] = 0.6089432357797879;
      G[m][19][0] = 0.6089432357797879;
      G[m][19][1] = 0.115343494534698;
      G[m][20][0] = 0.6089432357797879;
      G[m][20][1] = 0.275713269685514;
      G[m][21][0] = 0.022838332222257;
      G[m][21][1] = 0.28132558098994;
      G[m][22][0] = 0.022838332222257;
      G[m][22][1] = 0.6958360867878031;
      G[m][23][0] = 0.28132558098994;
      G[m][23][1] = 0.022838332222257;
      G[m][24][0] = 0.28132558098994;
      G[m][24][1] = 0.6958360867878031;
      G[m][25][0] = 0.6958360867878031;
      G[m][25][1] = 0.022838332222257;
      G[m][26][0] = 0.6958360867878031;
      G[m][26][1] = 0.28132558098994;
      G[m][27][0] = 0.02573405054833;
      G[m][27][1] = 0.116251915907597;
      G[m][28][0] = 0.02573405054833;
      G[m][28][1] = 0.858014033544073;
      G[m][29][0] = 0.116251915907597;
      G[m][29][1] = 0.02573405054833;
      G[m][30][0] = 0.116251915907597;
      G[m][30][1] = 0.858014033544073;
      G[m][31][0]= 0.858014033544073;
      G[m][31][1] =0.02573405054833;
      G[m][32][0] =0.858014033544073;
      G[m][32][1]= 0.116251915907597;

      W[m][0] = 0.5 * 0.025731066440455;
      W[m][1] = 0.5 * 0.025731066440455;
      W[m][2] = 0.5 * 0.025731066440455;
      W[m][3] = 0.5 * 0.043692544538038;
      W[m][4] = 0.5 * 0.043692544538038;
      W[m][5] = 0.5 * 0.043692544538038;
      W[m][6] = 0.5 * 0.062858224217885;
      W[m][7] = 0.5 * 0.062858224217885;
      W[m][8] = 0.5 * 0.062858224217885;
      W[m][9] = 0.5 * 0.034796112930709;
      W[m][10] = 0.5 * 0.034796112930709;
      W[m][11] = 0.5 * 0.034796112930709;
      W[m][12] = 0.5 * 0.006166261051559;
      W[m][13] = 0.5 * 0.006166261051559;
      W[m][14] = 0.5 * 0.006166261051559;
      W[m][15] = 0.5 * 0.040371557766381;
      W[m][16] = 0.5 * 0.040371557766381;
      W[m][17] = 0.5 * 0.040371557766381;
      W[m][18] = 0.5 * 0.040371557766381;
      W[m][19] = 0.5 * 0.040371557766381;
      W[m][20] = 0.5 * 0.040371557766381;
      W[m][21] = 0.5 * 0.022356773202303;
      W[m][22] = 0.5 * 0.022356773202303;
      W[m][23] = 0.5 * 0.022356773202303;
      W[m][24] = 0.5 * 0.022356773202303;
      W[m][25] = 0.5 * 0.022356773202303;
      W[m][26] = 0.5 * 0.022356773202303;
      W[m][27] = 0.5 * 0.017316231108659;
      W[m][28] = 0.5 * 0.017316231108659;
      W[m][29] = 0.5 * 0.017316231108659;
      W[m][30] = 0.5 * 0.017316231108659;
      W[m][31] = 0.5 * 0.017316231108659;
      W[m][32] = 0.5 * 0.017316231108659;
      O[m] = 12;
    }

    FieldVector<double, 2> point(int m, int i)
    {
      return G[m][i];
    }

    double weight (int m, int i)
    {
      return W[m][i];
    }

    int order (int m)
    {
      return O[m];
    }

  private:
    FieldVector<double, 2> G[MAXP+1][MAXP];

    double W[MAXP+1][MAXP];     // weights associated with points
    int O[MAXP+1];              // order of the rule
  };

  template<typename ct>
  SimplexQuadratureRule<ct,2>::SimplexQuadratureRule(int p) : QuadratureRule<ct,2>(GeometryType(GeometryType::simplex, 2))
  {
    int m;
    if (p>highest_order)
      DUNE_THROW(QuadratureOrderOutOfRange,
                 "QuadratureRule for order " << p << " and GeometryType "
                                             << this->type() << " not available");

    if (p>SimplexQuadraturePoints<2>::highest_order)
    {
      // Define the quadrature rules...
      QuadratureRule<ct,1> gauss1D =
        QuadratureRules<ct,1>::rule(GeometryType::cube, p, QuadratureType::Gauss);
      QuadratureRule<ct,1> jac1D =
        QuadratureRules<ct,1>::rule(GeometryType::cube, p, QuadratureType::Jacobian_1_0);

      // Compute the conical product
      for (typename QuadratureRule<ct,1>::const_iterator
           gp=gauss1D.begin(); gp!=gauss1D.end(); ++gp)
      {
        for (typename QuadratureRule<ct,1>::const_iterator
             jp=jac1D.begin(); jp!=jac1D.end(); ++jp)
        {
          // compute coordinates and weight
          double weight = 1.0;
          FieldVector<ct,2> local(0.0);
          local[0] = jp->position()[0];
          local[1] = gp->position()[0] * (1. - jp->position()[0]);
          weight   = gp->weight() * jp->weight() * (1. - jp->position()[0]);
          // put in container
          push_back(QuadraturePoint<ct,d>(local,weight));
        }
      }
      this->delivered_order = std::min(gauss1D.order(), jac1D.order());
      return;
    }

    switch(p)
    {
    case 0 : // to be verified
      m=1; // to be verified
      break;
    case 1 :
      m=1;
      break;
    case 2 :
      m=3;
      break;
    case 3 :
      m=4;
      break;
    case 4 :
      m=6;
      break;
    case 5 :
      m=7;
      break;
    case 6 :
      m=12;
      break;
    case 7 :
      m=12;
      break;
    case 8 :
      m=16;
      break;
    case 9 :
      m=19;
      break;
    case 10 :
      m=25;
      break;
    case 11 :
      m=28;
      break;
    case 12 :
      m=33;
      break;
    default : m=33;
    }
    this->delivered_order = SimplexQuadraturePointsSingleton<2>::sqp.order(m);
    FieldVector<ct, d> local;
    double weight;
    for(int i=0; i<m; ++i)
    {
      for(int k=0; k<d; ++k)
        local[k]=SimplexQuadraturePointsSingleton<2>::sqp.point(m,i)[k];
      weight=SimplexQuadraturePointsSingleton<2>::sqp.weight(m,i);
      // put in container
      push_back(QuadraturePoint<ct,d>(local,weight));
    }
  }

  //!
  template<>
  class SimplexQuadraturePoints<3>
  {
  public:
    enum { MAXP=15};
    enum { highest_order=5 };

    //! initialize quadrature points on the interval for all orders
    SimplexQuadraturePoints()
    {
      int m = 0;
      O[m] = 0;

      // polynom degree 1
      m = 1;
      G[m][0][0] = 0.25;
      G[m][0][1] = 0.25;
      G[m][0][2] = 0.25;

      W[m][0] = 1.0/6.0;
      O[m] = 1;

      // polynom degree 2
      // symmetric
      m = 4;
      static const double m_4_a = 0.585410196624968500;
      static const double m_4_b = 0.138196601125010500;
      G[m][0] = m_4_b;
      G[m][1] = m_4_b;
      G[m][2] = m_4_b;
      G[m][3] = m_4_b;
      G[m][0][0] = m_4_a;
      G[m][1][1] = m_4_a;
      G[m][2][2] = m_4_a;

      W[m][0] = 1.0/4.0/6.0;
      W[m][1] = 1.0/4.0/6.0;
      W[m][2] = 1.0/4.0/6.0;
      W[m][3] = 1.0/4.0/6.0;
      O[m] = 2;

      // polynom degree 3
      // symmetric
      m = 8;
      G[m][0][0] = 0.0;
      G[m][0][1] = 0.0;
      G[m][0][2] = 0.0;
      G[m][1][0] = 1.0;
      G[m][1][1] = 0.0;
      G[m][1][2] = 0.0;
      G[m][2][0] = 0.0;
      G[m][2][1] = 1.0;
      G[m][2][2] = 0.0;
      G[m][3][0] = 0.0;
      G[m][3][1] = 0.0;
      G[m][3][2] = 1.0;
      G[m][4][0] = 1.0/3.0;
      G[m][4][1] = 1.0/3.0;
      G[m][4][2] = 0.0;
      G[m][5][0] = 1.0/3.0;
      G[m][5][1] = 0.0;
      G[m][5][2] = 1.0/3.0;
      G[m][6][0] = 0.0;
      G[m][6][1] = 1.0/3.0;
      G[m][6][2] = 1.0/3.0;
      G[m][7][0] = 1.0/3.0;
      G[m][7][1] = 1.0/3.0;
      G[m][7][2] = 1.0/3.0;
      W[m][0] = 0.025/6.0;
      W[m][1] = 0.025/6.0;
      W[m][2] = 0.025/6.0;
      W[m][3] = 0.025/6.0;
      W[m][4] = 0.225/6.0;
      W[m][5] = 0.225/6.0;
      W[m][6] = 0.225/6.0;
      W[m][7] = 0.225/6.0;
      O[m] = 3;


      // polynomial degree 5
      // symmetric points
      static const double s_1=0.09197107805272303279;     /* (7 - sqrt(15) ) / 34 */
      static const double s_2=0.31979362782962990839;     /* (7 + sqrt(15) ) / 34 */
      static const double t_1=0.72408676584183090164;     /* (13 + 3*sqrt(15) ) / 34 */
      static const double t_2=0.04061911651111027484;     /* (13 - 3*sqrt(15) ) / 34 */
      static const double u  =0.05635083268962915574;     /* (10 - 2*sqrt(15) ) / 40 */
      static const double v  =0.44364916731037084426;     /* (10 + 2*sqrt(15) ) / 40 */
      static const double A  =0.019753086419753086420;    /* 16 / 135 / vol */
      static const double B_1=0.011989513963169770001;    /* (2665 + 14*sqrt(15) ) / 37800 / vol */
      static const double B_2=0.011511367871045397547;    /* (2665 - 14*sqrt(15) ) / 37800 / vol */
      static const double C  =0.0088183421516754850088;   /* 20 / 378 / vol */

      m=15;
      G[m][0][0] = 0.25;
      G[m][0][1] = 0.25;
      G[m][0][2] = 0.25;
      G[m][1][0] = s_1;
      G[m][1][1] = s_1;
      G[m][1][2] = s_1;
      G[m][2][0] = t_1;
      G[m][2][1] = s_1;
      G[m][2][2] = s_1;
      G[m][3][0] = s_1;
      G[m][3][1] = t_1;
      G[m][3][2] = s_1;
      G[m][4][0] = s_1;
      G[m][4][1] = s_1;
      G[m][4][2] = t_1;
      G[m][5][0] = s_2;
      G[m][5][1] = s_2;
      G[m][5][2] = s_2;
      G[m][6][0] = t_2;
      G[m][6][1] = s_2;
      G[m][6][2] = s_2;
      G[m][7][0] = s_2;
      G[m][7][1] = t_2;
      G[m][7][2] = s_2;
      G[m][8][0] = s_2;
      G[m][8][1] = s_2;
      G[m][8][2] = t_2;
      G[m][9][0] = v;
      G[m][9][1] = u;
      G[m][9][2] = u;
      G[m][10][0] = u;
      G[m][10][1] = v;
      G[m][10][2] = u;
      G[m][11][0] = u;
      G[m][11][1] = u;
      G[m][11][2] = v;
      G[m][12][0] = v;
      G[m][12][1] = v;
      G[m][12][2] = u;
      G[m][13][0] = v;
      G[m][13][1] = u;
      G[m][13][2] = v;
      G[m][14][0] = u;
      G[m][14][1] = v;
      G[m][14][2] = v;

      W[m][0] = A;
      W[m][1] = B_1;
      W[m][2] = B_1;
      W[m][3] = B_1;
      W[m][4] = B_1;
      W[m][5] = B_2;
      W[m][6] = B_2;
      W[m][7] = B_2;
      W[m][8] = B_2;
      W[m][9] = C;
      W[m][10] = C;
      W[m][11] = C;
      W[m][12] = C;
      W[m][13] = C;
      W[m][14] = C;
      O[m] = 5;

    }

    FieldVector<double, 3> point(int m, int i)
    {
      return G[m][i];
    }

    double weight (int m, int i)
    {
      return W[m][i];
    }

    int order (int m)
    {
      return O[m];
    }

  private:
    FieldVector<double, 3> G[MAXP+1][MAXP];
    double W[MAXP+1][MAXP];     // weights associated with points
    int O[MAXP+1];              // order of the rule
  };

  template<typename ct>
  SimplexQuadratureRule<ct,3>::SimplexQuadratureRule(int p) : QuadratureRule<ct,3>(GeometryType(GeometryType::simplex, 3))
  {
    int m;
    if (p>highest_order)
      DUNE_THROW(QuadratureOrderOutOfRange,
                 "QuadratureRule for order " << p << " and GeometryType "
                                             << this->type() << " not available");

    // quadrature rules >= 3 are known to work.
    if (p>SimplexQuadraturePoints<3>::highest_order)
    {
      // Define the quadrature rules...
      QuadratureRule<ct,1> gauss1D =
        QuadratureRules<ct,1>::rule(GeometryType::cube, p, QuadratureType::Gauss);
      QuadratureRule<ct,1> jacA1D =
        QuadratureRules<ct,1>::rule(GeometryType::cube, p, QuadratureType::Jacobian_1_0);
      QuadratureRule<ct,1> jacB1D =
        QuadratureRules<ct,1>::rule(GeometryType::cube, p, QuadratureType::Jacobian_2_0);

      // Compute the tensor product

      // All rules should be of the same order
      assert(gauss1D.size() == jacA1D.size());
      assert(gauss1D.size() == jacB1D.size());

      // Compute the conical product
      for (typename QuadratureRule<ct,1>::const_iterator
           gp=gauss1D.begin(); gp!=gauss1D.end(); ++gp)
      {
        for (typename QuadratureRule<ct,1>::const_iterator
             j1p=jacA1D.begin(); j1p!=jacA1D.end(); ++j1p)
        {
          for (typename QuadratureRule<ct,1>::const_iterator
               j2p=jacB1D.begin(); j2p!=jacB1D.end(); ++j2p)
          {
            // compute coordinates and weight
            double weight = 1.0;
            FieldVector<ct, d> local;
            local[0] = j2p->position()[0];
            local[1] = j1p->position()[0] * (1.0-j2p->position()[0]);
            local[2] = gp->position()[0] * (1.-j1p->position()[0]) * (1.0-j2p->position()[0]);
            weight   = (1.0-j2p->position()[0]) * (1.-j1p->position()[0]) * (1.0-j2p->position()[0])
                       * gp->weight() * j1p->weight() * j2p->weight();
            // put in container
            push_back(QuadraturePoint<ct,d>(local,weight));
          }
        }
      }
      this->delivered_order = std::min(gauss1D.order(), std::min(jacA1D.order(), jacB1D.order()));
      return;
    }

    switch(p)
    {
    case 0 : // to be verified
      m=1; // to be verified
      break;
    case 1 :
      m=1;
      break;
    case 2 :
      m=4;
      break;
    case 3 :
      m=8;
      break;
    case 4 :
    case 5 :
      m=15;
      break;
    default : m=15;
    }
    this->delivered_order = SimplexQuadraturePointsSingleton<3>::sqp.order(m);
    FieldVector<ct, d> local;
    double weight;
    for(int i=0; i<m; ++i)
    {
      for(int k=0; k<d; ++k)
        local[k]=SimplexQuadraturePointsSingleton<3>::sqp.point(m,i)[k];
      weight=SimplexQuadraturePointsSingleton<3>::sqp.weight(m,i);
      // put in container
      push_back(QuadraturePoint<ct,d>(local,weight));

    }

  }

  /** Singleton holding the Gauss points on the interval */
  SimplexQuadraturePoints<2> SimplexQuadraturePointsSingleton<2>::sqp;

  /** Singleton holding the SimplexQuadrature points dim==3 */
  SimplexQuadraturePoints<3> SimplexQuadraturePointsSingleton<3>::sqp;

  /** Singleton holding the Prism Quadrature points  */
  PrismQuadraturePoints<3> PrismQuadraturePointsSingleton<3>::prqp;

  /** Singleton holding the Quadrature points  */
  PyramidQuadraturePoints PyramidQuadraturePointsSingleton<3>::pyqp;

  template SimplexQuadratureRule<float, 2>::SimplexQuadratureRule(int);
  template SimplexQuadratureRule<double, 2>::SimplexQuadratureRule(int);
  template SimplexQuadratureRule<float, 3>::SimplexQuadratureRule(int);
  template SimplexQuadratureRule<double, 3>::SimplexQuadratureRule(int);

} // namespace
