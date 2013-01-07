#include <Buffer.h>
#include <FastMath.h>

Buffer::Buffer()
{
	;
}

// Constructeur de recopie interdit
Buffer::Buffer(const Buffer & b)
{
	;
}
Buffer & Buffer::operator=(const Buffer & b)
{
	return * this;
}

wxImage & Buffer::GetImage()
{
	return data;
}

void Buffer::SetPoint(const Coord2D & pos, const Color & c)
{
	if (pos.x < 0 || pos.x >= width)
		return;
	if (pos.y < 0 || pos.y >= height)
		return;
	// S'il faut remplacer le pixel de coordonnées (pos.x,pos.y) alors on le dessine
	if (zbuffer.ReplaceCurrent(pos))
		data.SetRGB(pos.x, pos.y, c.red, c.green, c.blue);
}

void Buffer::ClearBuffer()
{
	data.SetRGB(wxRect(0, 0, width, height), 0, 64, 64);
}

void Buffer::SetSize(wxSize size)
{
	data.Destroy();
	data.Create(size.GetWidth(), size.GetHeight(), false);
	width = size.GetWidth();
	height = size.GetHeight();
	scanLineComputer.SetSize(size);
	zbuffer.SetSize(size);
}

bool Buffer::SaveToFile(const wxString& name) const
{
	return data.SaveFile(name);
}

//Doit afficher une croix
void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
		const Color c2)
{
	// Implémentation de l'algo en Pascal
	int x, y;
	int longX, longY;
	int critere;
	int const1, const2;
	int incX, incY;
	int compteur;
	double distance = p1.Distance(p2);

	x = p1.x;
	y = p1.y;

    // Calcul des longueurs entre les points
	longX = p2.x - x;
	longY = p2.y - y;

    // Si la longueur est inférieure à 0, c'est que x1 est "avant" x2
    // on devra donc décrémenter X plutôt que l'incrémenter. On inverse la longueur
	if(longX >= 0)
	{
        incX = 1;
	}
	else
	{
        incX = -1;
        longX = -longX;
	}

    // Idem que pour X
	if(longY >= 0 )
	{
	    incY = 1;
	}
	else
	{
	    incY = -1;
	    longY = -longY;
	}

    // Dessin du point : les opérations se font selon l'octant
	if(longY < longX)
	{
	    const1 = 2 * (longY - longX);
	    const2 = 2 * longY;

	    critere = const2 - longX;

	    for(compteur = 1; compteur <= longX; compteur++)
	    {
	        Coord2D coord(x, y);

            // Calcul de la distance est des poids
	        double distCourante = p1.Distance(coord);
	        double w1 = 1.0 - (distCourante / distance);
	        double w2 = 1.0 - w1;

            // Dessin
	        SetPoint(coord, c1*w1 + c2*w2);

            // Incrémentation des coordonnées pour le prochain passage
	        if(critere > 0)
	        {
	            y +=incY;
	            critere +=const1;
	        }
	        else
	        {
	            critere += const2;
	        }

	        x += incX;
	    }
	}
	else
	{
	    const1 = 2 * (longX - longY);
	    const2 = 2 * longX;

	    critere = const2 - longY;

	    for(compteur = 1; compteur <= longY; compteur++)
	    {
	        Coord2D coord(x, y);

	        // Calcul de la distance est des poids
	        double distCourante = p1.Distance(coord);
	        double w1 = 1.0 - (distCourante / distance);
	        double w2 = 1.0 - w1;

            // Dessin
	        SetPoint(coord, c1*w1 + c2*w2);

            // Incrémentation des coordonnées pour le prochain passage
	        if(critere > 0)
	        {
	            x += incX;
	            critere += const1;
	        }
	        else
	        {
                critere += const2;
	        }

	        y += incY;
	    }
	}
}

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    scanLineComputer.Init();
    scanLineComputer.Compute( p1, p2, p3 );

    // Dessin des contours
    DrawLine(p1, p2, c1, c2) ;
    DrawLine(p2, p3, c2, c3) ;
    DrawLine(p3, p1, c3, c1) ;

    // Dessin de l'intérieur du triangle, ligne par ligne
    for( int i = scanLineComputer.ymin; i < scanLineComputer.ymax; ++i )
    {
        Color color1 = ( c1 * scanLineComputer.leftweight.data[i].data[0] ) + ( c2 * scanLineComputer.leftweight.data[i].data[1] ) + ( c3 * scanLineComputer.leftweight.data[i].data[2] );
        Color color2 = ( c1 * scanLineComputer.rightweight.data[i].data[0] ) + ( c2 * scanLineComputer.rightweight.data[i].data[1] ) + ( c3 * scanLineComputer.rightweight.data[i].data[2] );
        DrawLine( Coord2D( scanLineComputer.left.data[i], i), Coord2D( scanLineComputer.right.data[i], i ) ,color1, color2 );
    }

}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	scanLineComputer.Init();
    scanLineComputer.Compute( p1, p2, p3 );

    Color colorLeft, colorRight;
    Coord3D current3D, leftPosi, rightPosi, normalLeft, normalRight;

    // Parcours de chaque ligne
    for( int i = scanLineComputer.ymin; i < scanLineComputer.ymax; ++i )
    {
        Coord2D pointLeft(scanLineComputer.left.data[i], i);
        Coord2D pointRight(scanLineComputer.right.data[i], i);
        double distance = pointLeft.Distance(pointRight);

        normalLeft = normal1 * scanLineComputer.leftweight.data[i].data[0] +
                normal2 * scanLineComputer.leftweight.data[i].data[1] +
                normal3 * scanLineComputer.leftweight.data[i].data[2];

        normalRight = normal1 * scanLineComputer.rightweight.data[i].data[0] +
                normal2 * scanLineComputer.rightweight.data[i].data[1] +
                normal3 * scanLineComputer.rightweight.data[i].data[2];

        colorLeft = c1 * scanLineComputer.leftweight.data[i].data[0] +
                c2 * scanLineComputer.leftweight.data[i].data[1] +
                c3 * scanLineComputer.leftweight.data[i].data[2];

        colorRight = c1 * scanLineComputer.rightweight.data[i].data[0] +
                c2 * scanLineComputer.rightweight.data[i].data[1] +
                c3 * scanLineComputer.rightweight.data[i].data[2];

        leftPosi = posi1 * scanLineComputer.leftweight.data[i].data[0] +
                posi2 * scanLineComputer.leftweight.data[i].data[1] +
                posi3 * scanLineComputer.leftweight.data[i].data[2];

        rightPosi = posi1 * scanLineComputer.rightweight.data[i].data[0] +
                posi2 * scanLineComputer.rightweight.data[i].data[1] +
                posi3 * scanLineComputer.rightweight.data[i].data[2];

        // Parcours et dessin de tous les points sur la ligne courante
		for(int j = scanLineComputer.left.data[i]; j <= scanLineComputer.right.data[i]; ++j)
		{
		    Coord2D current2D(j, i);
		    double w1 = 1.0 - (pointLeft.Distance(current2D) / distance);
		    double w2 = 1.0 - w1;

		    Coord3D posiCurrent = leftPosi * w1 + rightPosi * w2;
		    Coord3D normalCurrent = normalLeft * w1 + normalRight * w2;

		    Color diffuseColor = pointLight.GetColor(posiCurrent, normalCurrent);
		    Color pointColor = colorLeft * w1 + colorRight * w2;

		    SetPoint(current2D, (ambientLight.ambientColor + diffuseColor) * pointColor);

        }

    }
}

