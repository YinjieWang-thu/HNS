void makescript()
{
    Double_t E_p = 9.3;//GeV
    Double_t m1 = 0.938272;//proton
    Double_t m2 = 0.938272;//0.939565 if neutron

    Double_t E_cm = sqrt(m1*m1+m2*m2+2*E_p*m2);
    Double_t bz = sqrt(E_p*E_p-m1*m1)/(E_p+m2);

    char* s1 = new char[1024];
    char* s2 = new char[1024];

    sprintf(s1, "sed -e 's/Beams:eCM = /Beams:eCM = %.4f/' run_template.sh > run.sh", E_cm);
    sprintf(s2, "sed -e 's/double bz = /double bz = %.4f/' myjam_template.C > myjam.C", bz);

    system("rm -f myjam.C run.sh");
    system(s1);
    system(s2);

    if(m2 > 0.939)
    {
        system("sed -i -e 's/beamB = p+/beamB = n/' run.sh ");
    }

    gROOT->ProcessLine(".q");
}