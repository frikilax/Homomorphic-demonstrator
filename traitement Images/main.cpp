#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <seal/seal.h>
#include "operations.cpp"

using namespace std;
using namespace seal;

#include "header.h"

int main(int argc, char* argv[])
{
	 if(argc < 2) abort();

	string polyModulus = "1x^1024 + 1";
    
	auto coeffModulus = coeff_modulus_128(2048);

	int plainModulus = 40961;       //valeur marche pour toutes les puissances de 2 jusqu'à 8192 (poly_modulus)
                                    //attention, réduit significativement le bruit disponible (peut être compensé par un coeff modulus plus grand, mais réduit la sécurité (?))

    int dynamiqueValeursPlain = 256;    //peut être modifié si on travaille avec des valeurs comportant une autre dynamique (si on veux inverser des int par exemple)

	EncryptionParameters parameters;

	parameters.set_poly_modulus(polyModulus);
	parameters.set_coeff_modulus(coeffModulus);
	parameters.set_plain_modulus(plainModulus);

	SEALContext context(parameters);

	auto qualifiers = context.qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.enable_batching << endl;

	ImagePlaintext monImage(context, argv[1]);
	monImage.printParameters();
	monImage.printOperations();

	ImageCiphertext imageCryptee(monImage);

	imageCryptee.encrypt(monImage);
	ImageCiphertext imageLoaded(imageCryptee);	//créée en tant que copie de l'imageCryptée

	imageCryptee.save();
	imageLoaded.load();

	imageLoaded.grey();
	imageLoaded.printOperations();

	ImagePlaintext imageFinale = imageLoaded.decrypt();
	imageFinale.printOperations();

	imageFinale.toImage("imageNegate.png");

	return 0;
}