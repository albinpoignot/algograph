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
	//Color colorToDraw = c1*c2;

    int e = p2.x - p1.x;
    int dx = 2 * e;
    int dy = ( p2.y - p1.y ) * 2;

    int x1 = p1.x;
    int x2 = p2.x;
    int y1 = p1.y;

    while( x1 < x2 )
    {
        Coord2D toTrace( x1, y1 );
        SetPoint( toTrace, c1 );
        x1 += 1;

        e -= dy;
        if( e <= 0 )
        {
            y1 += 1;
            e += dx;
        }
        else
        {
            y1 -= 1;
            e -= dx;
        }
    }

    SetPoint(p2, c2);

}

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    int minX = FastMath::min<int>( p1.x, p2.x );
    minX = FastMath::min<int>( p3.x, minX );

    int maxX = FastMath::max<int>( p1.x, p2.x );
    maxX = FastMath::max<int>( p3.x, maxX );

    int minY = FastMath::min<int>( p1.y, p2.y );
    minY = FastMath::min<int>( p3.y, minY );

    int maxY = FastMath::max<int>( p1.y, p2.y );
    maxY = FastMath::max<int>( p3.y, maxY );

    for( int i = minX; i < maxX; ++i )
        for( int j = minY; j < maxY; ++j )
            if( isInside( p1, p2, p3, Coord2D(i,j) ) )
                SetPoint( Coord2D(i,j), c1 );

}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
}

bool Buffer::isInside( Coord2D a, Coord2D b, Coord2D c, Coord2D point )
{
    return ( isRight( a,b, point ) && isRight( b,c, point ) && isRight( c,a , point ) );
}

bool Buffer::isRight( Coord2D a, Coord2D b, Coord2D point )
{
    return ( (b.x - a.x) * ( point.y - a.y ) - ( point.x - a.x ) * ( b.y - a.y ) ) > 0;
}
