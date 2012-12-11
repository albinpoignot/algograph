#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

#include <iostream>

// le constructeur
Renderer::Renderer(Panel3D * _owner, Engine * _engine) :
	owner(_owner), engine(_engine), drawable(&_engine->drawable),
			effectiveDrawable(&_engine->effectiveDrawable), ambientLight(Color(
					16, 16, 16)), pointLight(Coord3D(0, 0, 100), Color(255,
					255, 255))
{
	currentBuffer = 0;
	lastBufferAvailiable = -1;
	buffer = &buffers[currentBuffer];

	width = 0;
	height = 0;
	current = false;
}

Renderer::~Renderer()
{
	;
}

// pour dessiner le dernier buffer disponible sur le DC
void Renderer::DrawBufferOnDC(wxDC & dc)
{
	// si aucun buffer valide n'est disponible, on ne dessine pas
	if (lastBufferAvailiable != -1)
	{
		// on dessine le dernier buffer disponible
		wxBitmap bitmap(buffers[lastBufferAvailiable].GetImage() );
		dc.DrawBitmap(bitmap, 0, 0);
	}
}

// pour dimensionner les buffers
void Renderer::SetSize(wxSize _size)
{
	if (width != _size.GetWidth() || height != _size.GetHeight())
	{
		buffers[0].SetSize(_size);
		buffers[1].SetSize(_size);

		// reset de l'affichage
		lastBufferAvailiable = -1;
		currentBuffer = 0;
		buffer = &buffers[currentBuffer];

		width = _size.GetWidth();
		height = _size.GetHeight();
		size = _size;
	}
}

void Renderer::ReDraw()
{
	renderable.ComputeRenderable( *effectiveDrawable, size);
	Draw(); // on dessine
	// on échange les buffers
	lastBufferAvailiable = currentBuffer;
	currentBuffer = (currentBuffer + 1) % 2;
	buffer = &buffers[currentBuffer];
	owner->Refresh();
}

// Dessine la scène
void Renderer::Draw()
{
	Color red(255, 0, 0);
	Color green(0, 255, 0);
	buffer->ClearBuffer();
	if (current)
	{
		buffer->DrawLine(Coord2D(0, 0, 0), Coord2D(width, height, 0), green,
				green);
		buffer->DrawLine(Coord2D(width, 0, 0), Coord2D(0, height, 0), green,
				green);
	}
	else
	{
		buffer->DrawLine(Coord2D(0, 0, 0), Coord2D(width, height, 0), red, red);
		buffer->DrawLine(Coord2D(width, 0, 0), Coord2D(0, height, 0), red, red);
	}

	switch (mode)
	{
	case Filaire:
	{
		buffer->zbuffer.Disable();
		DrawFilaire();
		break;
	}
	case FilaireCache:
	{
		buffer->zbuffer.Disable();
		DrawFilaireCache();
		break;
	}
	case FacePleine:
	{
		buffer->zbuffer.Disable();
		DrawFacePleine();
		break;
	}
	case Lambert:
	{
		buffer->zbuffer.Disable();
		DrawLambert();
		break;
	}
	case Gouraud:
	{
		buffer->zbuffer.Disable();
		DrawGouraud();
		break;
	}
	case Phong:
	{
		buffer->zbuffer.Disable();
		DrawPhong();
		break;
	}
	case FacePleineZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawFacePleine();
		break;
	}
	case LambertZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawLambert();
		break;
	}
	case GouraudZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawGouraud();
		break;
	}
	case PhongZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawPhong();
		break;
	}

	};

}
void Renderer::DrawFilaire()
{
    for( int i = 0; i < drawable->faces.size; ++i )
	{
        Face current = drawable->faces.data[i];

        if( drawable->colorOnFace )
        {
            buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], drawable->pointColors.data[current.index1], drawable->pointColors.data[current.index2] );
            buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index3], drawable->pointColors.data[current.index1], drawable->pointColors.data[current.index3] );
            buffer->DrawLine( renderable.points2D.data[current.index2], renderable.points2D.data[current.index3], drawable->pointColors.data[current.index2], drawable->pointColors.data[current.index3] );
        }
        else
        {
            Color color = drawable->faceColors.data[i];

            buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], color, color );
            buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index3], color, color );
            buffer->DrawLine( renderable.points2D.data[current.index2], renderable.points2D.data[current.index3], color, color );
        }
	}
}

void Renderer::DrawFilaireCache()
{
    for( int i = 0; i < drawable->faces.size; ++i )
    {
        Face current = drawable->faces.data[i];

        if( effectiveDrawable->faceVisibles.data[i] )
        {
            if( drawable->colorOnFace )
            {
                buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], drawable->pointColors.data[current.index1], drawable->pointColors.data[current.index2] );
                buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index3], drawable->pointColors.data[current.index1], drawable->pointColors.data[current.index3] );
                buffer->DrawLine( renderable.points2D.data[current.index2], renderable.points2D.data[current.index3], drawable->pointColors.data[current.index2], drawable->pointColors.data[current.index3] );
            }
            else
            {
                Color color = drawable->faceColors.data[i];

                buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], color, color );
                buffer->DrawLine( renderable.points2D.data[current.index1], renderable.points2D.data[current.index3], color, color );
                buffer->DrawLine( renderable.points2D.data[current.index2], renderable.points2D.data[current.index3], color, color );
            }
        }
    }
}
void Renderer::DrawFacePleine()
{
	for( int i = 0; i < drawable->faces.size; ++i )
    {
        Face current = drawable->faces.data[i];

        if( effectiveDrawable->faceVisibles.data[i] )
        {
            if( drawable->colorOnFace )
            {
                buffer->DrawFilledTriangle( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], renderable.points2D.data[current.index3],
                                            drawable->pointColors.data[current.index1], drawable->pointColors.data[current.index2], drawable->pointColors.data[current.index3] );

            }
            else
            {
                Color color = drawable->faceColors.data[i];

                buffer->DrawFilledTriangle( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], renderable.points2D.data[current.index3],
                                            color, color, color );
            }
        }
    }
}

void Renderer::DrawLambert()
{
	for( int i = 0; i < drawable->faces.size; ++i )
    {
        Face current = drawable->faces.data[i];

        if( effectiveDrawable->faceVisibles.data[i] )
        {
            Coord3D p1 = effectiveDrawable->points.data[current.index1];
            Coord3D p2 = effectiveDrawable->points.data[current.index2];
            Coord3D p3 = effectiveDrawable->points.data[current.index3];

            double baryCentreX = (p1.x + p2.x + p3.x) / 3;
            double baryCentreY = (p1.y + p2.y + p3.y) / 3;
            double baryCentreZ = (p1.z + p2.z + p3.z) / 3;

            Color colorLight = pointLight.GetColor( Coord3D( baryCentreX, baryCentreY, baryCentreZ), effectiveDrawable->faceNormals.data[i] );
            Color colorAmbient = ambientLight.ambientColor;
            Color color = colorLight + colorAmbient;

            if( drawable->colorOnFace )
            {
                buffer->DrawFilledTriangle( renderable.points2D.data[current.index1],
                                            renderable.points2D.data[current.index2],
                                            renderable.points2D.data[current.index3],
                                            drawable->pointColors.data[current.index1]*color,
                                            drawable->pointColors.data[current.index2]*color,
                                            drawable->pointColors.data[current.index3]*color );
            }
            else
            {
                Color colorCurrent = drawable->faceColors.data[i];

                buffer->DrawFilledTriangle( renderable.points2D.data[current.index1], renderable.points2D.data[current.index2], renderable.points2D.data[current.index3],
                                            colorCurrent*color, colorCurrent*color, colorCurrent*color );
            }
        }
    }
}

void Renderer::DrawGouraud()
{
	for( int i = 0; i < drawable->faces.size; ++i )
    {
        Face current = drawable->faces.data[i];

        if( effectiveDrawable->faceVisibles.data[i] )
        {
            // Récupère les coordonnées 3D des sommets
            Coord3D p1 = effectiveDrawable->points.data[current.index1];
            Coord3D p2 = effectiveDrawable->points.data[current.index2];
            Coord3D p3 = effectiveDrawable->points.data[current.index3];

            // Récupération des couleurs par rapport à la lumière
            Color colorP1 = pointLight.GetColor( p1, effectiveDrawable->pointNormals.data[current.index1] );
            Color colorP2 = pointLight.GetColor( p2, effectiveDrawable->pointNormals.data[current.index2] );
            Color colorP3 = pointLight.GetColor( p3, effectiveDrawable->pointNormals.data[current.index3] );

            // Ajout de ambient light
            Color colorAmbient = ambientLight.ambientColor;
            colorP1 = colorP1 + colorAmbient;
            colorP2 = colorP2 + colorAmbient;
            colorP3 = colorP3 + colorAmbient;

            // Dessin
            if( drawable->colorOnFace )
            {
                buffer->DrawFilledTriangle( renderable.points2D.data[current.index1],
                                            renderable.points2D.data[current.index2],
                                            renderable.points2D.data[current.index3],
                                            drawable->pointColors.data[current.index1]*colorP1,
                                            drawable->pointColors.data[current.index2]*colorP2,
                                            drawable->pointColors.data[current.index3]*colorP3 );
            }
            else
            {
                Color colorCurrent = drawable->faceColors.data[i];

                buffer->DrawFilledTriangle( renderable.points2D.data[current.index1],
                                            renderable.points2D.data[current.index2],
                                            renderable.points2D.data[current.index3],
                                            colorCurrent*colorP1,
                                            colorCurrent*colorP2,
                                            colorCurrent*colorP3 );
            }
        }
    }
}
void Renderer::DrawPhong()
{
	for( int i = 0; i < drawable->faces.size; ++i )
    {
        Face current = drawable->faces.data[i];

        if( effectiveDrawable->faceVisibles.data[i] )
        {
            // Récupération des Coord3D des points à dessiner
            Coord3D posi1 = effectiveDrawable->points.data[current.index1];
            Coord3D posi2 = effectiveDrawable->points.data[current.index2];
            Coord3D posi3 = effectiveDrawable->points.data[current.index3];

            if( drawable->colorOnFace )
            {
                buffer->DrawPhongTriangle(
                                        renderable.points2D.data[current.index1],
                                        renderable.points2D.data[current.index2],
                                        renderable.points2D.data[current.index3],
                                        drawable->pointColors.data[current.index1],
                                        drawable->pointColors.data[current.index2],
                                        drawable->pointColors.data[current.index3],
                                        posi1, posi2, posi3,
                                        effectiveDrawable->pointNormals.data[current.index1],
                                        effectiveDrawable->pointNormals.data[current.index2],
                                        effectiveDrawable->pointNormals.data[current.index3],
                                        ambientLight, pointLight);
            }
            else
            {
                Color colorCurrent = drawable->faceColors.data[i];

                buffer->DrawPhongTriangle(
                                        renderable.points2D.data[current.index1],
                                        renderable.points2D.data[current.index2],
                                        renderable.points2D.data[current.index3],
                                        colorCurrent,
                                        colorCurrent,
                                        colorCurrent,
                                        posi1, posi2, posi3,
                                        effectiveDrawable->pointNormals.data[current.index1],
                                        effectiveDrawable->pointNormals.data[current.index2],
                                        effectiveDrawable->pointNormals.data[current.index3],
                                        ambientLight, pointLight);
            }
        }
    }
}
