/* Rusu Marius Grupa 144
Compilator GNU GCC - CodeBlocks
Laborant [redacted] */


#include <iostream>
#include <exception>
#include <string>
#include <vector>



#define TotalBacterii 1000000000
#define TotalFungi 1500000
#define TotalVirusuri 100000000

class Exceptie : public std::exception
{
    const char* except;
public:
    Exceptie(const char* except = "") : except(except) {}

    const char* nume() const noexcept
    {
        return except;
    }
};


class Masca
{
protected:
    std::string protectie;
    bool model; // 0 - fara model, 1 - cu model
public:
    Masca(): protectie("") {}
    Masca(std::string protectie, bool model) : protectie(protectie), model(model) {}
    Masca(const Masca &m): protectie(m.protectie) {}
    ~Masca() {}

    friend std::istream& operator >>(std::istream&, Masca&);
    friend std::ostream& operator <<(std::ostream&, Masca&);

};

std::istream& operator >>(std::istream &f, Masca &m)
{
    std::cout<<"Protectie:";
    f>>m.protectie;
    std::cout<<"Model:";
    f>>m.protectie;
    return f;
}

std::ostream& operator <<(std::ostream &g, Masca &m)
{
    g<<m.protectie;
    if(m.model)g<<" cu model\n";
    return g;
}




class MascaPolicarbonat : public Masca
{
    std::string tip_prindere;
public:
    MascaPolicarbonat(): Masca(), tip_prindere("") {}
    MascaPolicarbonat(std::string protectie,bool model, std::string tip_prindere) : Masca(protectie,model), tip_prindere(tip_prindere) {}
    MascaPolicarbonat(const MascaPolicarbonat &m): Masca(m), tip_prindere(m.tip_prindere) {}
    ~MascaPolicarbonat() {}

    friend std::istream& operator >>(std::istream&, MascaPolicarbonat&);
    friend std::ostream& operator <<(std::ostream&, MascaPolicarbonat&);
};

std::istream& operator >>(std::istream &f, MascaPolicarbonat &m)
{
    std::cout<<"Protectie: ";
    f>>m.protectie;
    if(m.protectie != "ffp0")
    {
        throw Exceptie("Tip invalid de protectie");
    }
    std::cout<<"Model:";
    f>>m.protectie;
    std::cout<<"Tip prindere:";
    f>>m.tip_prindere;
    return f;
}

std::ostream& operator <<(std::ostream &g, MascaPolicarbonat &m)
{
    g<<m.protectie<<' '<<m.tip_prindere;
    if(m.model)g<<" cu model\n";
    return g;
}





class MascaChirurgicala : public Masca
{
    std::string culoare;
    int nr_pliuri;
public:
    MascaChirurgicala(): Masca(), culoare(""), nr_pliuri(0) {}
    MascaChirurgicala(std::string protectie,bool model, std::string culoare, int nr_pliuri) : Masca(protectie, model), culoare(culoare), nr_pliuri(nr_pliuri)  {}
    MascaChirurgicala(const MascaChirurgicala &m): Masca(m), culoare(m.culoare), nr_pliuri(m.nr_pliuri) {}
    ~MascaChirurgicala() {}

    friend std::istream& operator >>(std::istream&, MascaChirurgicala&);
    friend std::ostream& operator <<(std::ostream&, MascaChirurgicala&);
};

std::istream& operator >>(std::istream &f, MascaChirurgicala &m)
{
    std::cout<<"Protectie:";
    f>>m.protectie;
    if(m.protectie != "ffp1" && m.protectie != "ffp2" && m.protectie != "ffp3")
    {
        throw Exceptie("Tip invalid de protectie");
    }
    std::cout<<"Model:";
    f>>m.protectie;
    std::cout<<"Culoare:";
    f>>m.culoare;
    std::cout<<"Numar pliuri:";
    f>>m.nr_pliuri;
    return f;
}

std::ostream& operator <<(std::ostream &g, MascaChirurgicala &m)
{
    g<<m.protectie<<' '<<m.culoare<<' '<<m.nr_pliuri<<'\n';
    return g;
}






class Dezinfectant
{
protected:
    int nr_ingrediente;
    int nr_suprafete;
    std::vector<std::string> ingrediente;
    std::vector<std::string> suprafete;
    double eficienta;
public:
    Dezinfectant(): nr_ingrediente(0),nr_suprafete(0), ingrediente({""}), suprafete({""}), eficienta(0) {}
    Dezinfectant(int nr_ingrediente,int nr_suprafete,std::vector<std::string> ingrediente, std::vector<std::string> suprafete,double eficienta)
                    : nr_ingrediente(nr_ingrediente),nr_suprafete(nr_suprafete), ingrediente(ingrediente), suprafete(suprafete), eficienta(eficienta) {}

    Dezinfectant( const Dezinfectant &d) :  nr_ingrediente(d.nr_ingrediente),nr_suprafete(d.nr_suprafete),ingrediente(d.ingrediente), suprafete(d.suprafete), eficienta(d.eficienta) {}
    ~Dezinfectant(){}


    friend std::istream& operator >>(std::istream&, Dezinfectant&);
    friend std::ostream& operator <<(std::ostream&, Dezinfectant&);

};

std::istream& operator >>(std::istream &f, Dezinfectant &d)
{
    std::cout<<"Numar Ingrediente:";
    f>>d.nr_ingrediente;
    if(d.nr_ingrediente < 1)
    {
        throw Exceptie("Numar invalid");
    }
    std::string x;
    for(int i=1; i<=d.nr_ingrediente;++i)
    {
        f>>x;
        d.ingrediente.push_back(x);
    }
    std::cout<<"Numar Suprafete:";
    f>>d.nr_suprafete;
    if(d.nr_suprafete < 1)
    {
        throw Exceptie("Numar invalid");
    }
    for(int i=1; i<=d.nr_suprafete;++i)
    {
        f>>x;
        d.suprafete.push_back(x);
    }
    return f;
}

std::ostream& operator <<(std::ostream &g, Dezinfectant &d)
{
    g<<"Ingrediente: ";
    for(int i=1; i<=d.nr_ingrediente;++i)g<<d.ingrediente[i]<<' ';
    g<<'\n'<<"Suprafete: ";
    for(int i=1; i<=d.nr_suprafete;++i) g<<d.suprafete[i] <<' ';
    g<<'\n';
    return g;
}







class DezinfectantBacterii : virtual public Dezinfectant
{
protected:
    double bacterii_ucise;
public:
    DezinfectantBacterii(): Dezinfectant(), bacterii_ucise(0) {}
    DezinfectantBacterii(int nr_ingrediente,int nr_suprafete,std::vector<std::string> ingrediente, std::vector<std::string> suprafete,double eficienta, double bacterii_ucise)
                    : Dezinfectant(nr_ingrediente,nr_suprafete, ingrediente, suprafete,eficienta), bacterii_ucise(bacterii_ucise) {}

    DezinfectantBacterii( const DezinfectantBacterii &d) :  Dezinfectant(d), bacterii_ucise(d.bacterii_ucise) {}
    ~DezinfectantBacterii() {}

    DezinfectantBacterii& operator= ( const DezinfectantBacterii&);


    friend std::istream& operator >>(std::istream&, DezinfectantBacterii&);
    friend std::ostream& operator <<(std::ostream&, DezinfectantBacterii&);


};

DezinfectantBacterii& DezinfectantBacterii::operator= ( const DezinfectantBacterii& d)
{
    this->nr_ingrediente = d.nr_ingrediente;
    this->ingrediente = d.ingrediente;
    this->nr_suprafete;
    this->nr_suprafete=d.nr_suprafete;
    this->bacterii_ucise = d.bacterii_ucise;
    return *this;
}

std::istream& operator >>(std::istream &f, DezinfectantBacterii &d)
{
    f >> static_cast < Dezinfectant&> (d);
    std::cout<<"Bacterii ucise: ";
    f>>d.bacterii_ucise;
    d.eficienta= (d.bacterii_ucise/TotalBacterii)*100;
    return f;
}

std::ostream& operator <<(std::ostream &g, DezinfectantBacterii &d)
{
    g<<"Tip: Bacterie\n";
    g<< static_cast < Dezinfectant&> (d);
    g<<"Eficienta: ";
    g<< d.eficienta;
    return g;
}






class DezinfectantFungi : virtual public Dezinfectant
{
protected:
    double fungii_ucise;
public:
    DezinfectantFungi(): Dezinfectant(), fungii_ucise(0) {}
    DezinfectantFungi(int nr_ingrediente,int nr_suprafete,std::vector<std::string> ingrediente, std::vector<std::string> suprafete,double eficienta, double fungii_ucise)
                    : Dezinfectant(nr_ingrediente,nr_suprafete, ingrediente, suprafete,eficienta), fungii_ucise(fungii_ucise) {}

    DezinfectantFungi( const DezinfectantFungi &d) :  Dezinfectant(d), fungii_ucise(d.fungii_ucise) {}
    ~DezinfectantFungi() {}

    DezinfectantFungi& operator= ( const DezinfectantFungi&);


    friend std::istream& operator >>(std::istream&, DezinfectantFungi&);
    friend std::ostream& operator <<(std::ostream&, DezinfectantFungi&);
};

DezinfectantFungi& DezinfectantFungi::operator= ( const DezinfectantFungi& d)
{
    this->nr_ingrediente = d.nr_ingrediente;
    this->ingrediente = d.ingrediente;
    this->nr_suprafete;
    this->nr_suprafete=d.nr_suprafete;
    this->fungii_ucise = d.fungii_ucise;
    return *this;
}



std::istream& operator >>(std::istream &f, DezinfectantFungi &d)
{
    f >> static_cast < Dezinfectant&> (d);
    std::cout<<"Fungii ucise: ";
    f>>d.fungii_ucise;
    d.eficienta= (d.fungii_ucise/TotalFungi)*100;
    return f;
}

std::ostream& operator <<(std::ostream &g, DezinfectantFungi &d)
{
    g<<"Tip: Fungi\n";
    g<< static_cast < Dezinfectant&> (d);
    g<<"Eficienta: ";
    g<< d.eficienta;
    return g;
}






class DezinfectantVirusuri : virtual public Dezinfectant
{
protected:
    double virusuri_ucise;
public:
    DezinfectantVirusuri(): Dezinfectant(), virusuri_ucise(0) {}
    DezinfectantVirusuri(int nr_ingrediente,int nr_suprafete,std::vector<std::string> ingrediente, std::vector<std::string> suprafete, double eficienta, double virusuri_ucise)
                    : Dezinfectant(nr_ingrediente,nr_suprafete, ingrediente, suprafete, eficienta), virusuri_ucise(virusuri_ucise) {}

    DezinfectantVirusuri( const DezinfectantVirusuri &d) :  Dezinfectant(d), virusuri_ucise(d.virusuri_ucise) {}
    ~DezinfectantVirusuri() {}

    DezinfectantVirusuri& operator= ( const DezinfectantVirusuri&);


    friend std::istream& operator >>(std::istream&, DezinfectantVirusuri&);
    friend std::ostream& operator <<(std::ostream&, DezinfectantVirusuri&);

};


DezinfectantVirusuri& DezinfectantVirusuri::operator= ( const DezinfectantVirusuri& d)
{
    this->nr_ingrediente = d.nr_ingrediente;
    this->ingrediente = d.ingrediente;
    this->nr_suprafete;
    this->nr_suprafete=d.nr_suprafete;
    this->virusuri_ucise = d.virusuri_ucise;
    return *this;
}


std::istream& operator >>(std::istream &f, DezinfectantVirusuri &d)
{
    f >> static_cast < Dezinfectant&> (d);
    std::cout<<"Virusuri ucise: ";
    f>>d.virusuri_ucise;
    d.eficienta= (d.virusuri_ucise/TotalVirusuri)*100;
    return f;
}

std::ostream& operator <<(std::ostream &g, DezinfectantVirusuri &d)
{
    g<<"Tip: Virus\n";
    g<< static_cast < Dezinfectant&> (d);
    g<<"Eficienta: ";
    g<< d.eficienta;
    return g;
}




class DezinfectantToate : public DezinfectantBacterii, public DezinfectantFungi, public DezinfectantVirusuri // mostenire diamant
{
public:
    DezinfectantToate(): Dezinfectant(), DezinfectantBacterii(), DezinfectantFungi(), DezinfectantVirusuri() {}
    DezinfectantToate(int nr_ingrediente,int nr_suprafete,std::vector<std::string> ingrediente, std::vector<std::string> suprafete,double eficienta, double bacterii_ucise, double fungii_ucise, double virusuri_ucise)
        : Dezinfectant(nr_ingrediente,nr_suprafete, ingrediente, suprafete,eficienta), DezinfectantBacterii(nr_ingrediente,nr_suprafete, ingrediente, suprafete,eficienta, bacterii_ucise),
          DezinfectantFungi(nr_ingrediente,nr_suprafete, ingrediente, suprafete,eficienta, fungii_ucise), DezinfectantVirusuri(nr_ingrediente,nr_suprafete, ingrediente, suprafete,eficienta, virusuri_ucise) {}

    DezinfectantToate( const DezinfectantToate &d) : Dezinfectant(d), DezinfectantBacterii(d), DezinfectantFungi(d), DezinfectantVirusuri(d) {}
    ~DezinfectantToate() {}

    DezinfectantToate& operator= ( const DezinfectantToate&);

    friend std::istream& operator >>(std::istream&, DezinfectantToate&);
    friend std::ostream& operator <<(std::ostream&, DezinfectantToate&);

};

DezinfectantToate& DezinfectantToate::operator= ( const DezinfectantToate& d)
{
    this->nr_ingrediente = d.nr_ingrediente;
    this->ingrediente = d.ingrediente;
    this->nr_suprafete;
    this->nr_suprafete=d.nr_suprafete;
    this->bacterii_ucise = d.bacterii_ucise;
    this->fungii_ucise = d.fungii_ucise;
    this->virusuri_ucise = d.virusuri_ucise;
    return *this;
}

std::istream& operator >>(std::istream &f, DezinfectantToate &d)
{
    f >> static_cast < Dezinfectant&> (d);
    std::cout<<"Bacterii ucise: ";
    f>>d.bacterii_ucise;
    std::cout<<"Fungii ucise: ";
    f>>d.fungii_ucise;
    std::cout<<"Virusuri ucise: ";
    f>>d.virusuri_ucise;
    d.eficienta = ( d.bacterii_ucise + d.virusuri_ucise + d.fungii_ucise)/(TotalBacterii + TotalFungi+ TotalVirusuri) *100;
    return f;
}

std::ostream& operator <<(std::ostream &g, DezinfectantToate &d)
{
    g<<"Tip: Universal\n";
    g<< static_cast < Dezinfectant&> (d);
    g<<"Eficienta: ";
    g<< d.eficienta;
    return g;
}


class Achizitii
{
    std::string nume_client;
    std::string data;
    std::vector < Masca*> masti;
    std::vector < Dezinfectant*> dezinfectanti;
public:
    Achizitii() : nume_client(""), data("") {}
    Achizitii(std::string nume_client, std::string data) : nume_client(nume_client), data(data) {}
    Achizitii(const Achizitii&);
    ~Achizitii();

    void operator+=(const Masca&);
    void operator+=(const Dezinfectant&);

};


Achizitii::Achizitii(const Achizitii& a) : nume_client(a.nume_client), data(a.data)
{
    for(int i=0; i<a.masti.size();++i)
    {
        this->masti.push_back(new Masca(*a.masti[i]));
    }
    for(int i=0; i<a.dezinfectanti.size();++i)
    {
        this->dezinfectanti.push_back(new Dezinfectant(*a.dezinfectanti[i]));
    }
}

Achizitii::~Achizitii()
{
    for(int i=0; i< this->masti.size();++i)
    {
        delete this->masti[i];
    }
    for(int i=0; i< this->dezinfectanti.size();++i)
    {
        delete this->masti[i];
    }
}


void Achizitii::operator+=(const Masca& m)
{
    this->masti.push_back(new Masca(m));
}

void Achizitii::operator+=(const Dezinfectant& d)
{
    this->dezinfectanti.push_back(new Dezinfectant(d));
}

int main()
{
    MascaPolicarbonat a;
    try
    {
        std::cin>>a;
    }catch(Exceptie& ex)
    {
        std::cout<<ex.nume()<<'\n';
    }
    return 0;
}
