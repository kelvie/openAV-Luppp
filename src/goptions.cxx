

#include "goptions.hxx"

#include "eventhandler.hxx"

#include "controller/binding.hxx"


static void writeBindEnable(Fl_Widget* w, void* data)
{
  OptionsWindow* o = (OptionsWindow*) data;
  //LUPPP_NOTE("MIDI bind mode");
  
  Avtk::LightButton* l = (Avtk::LightButton*)w;
  l->value( !l->value() );
  
  EventControllerBindingEnable e( l->value() );
  writeToDspRingbuffer( &e );
}


OptionsWindow::OptionsWindow()
{
  window = new Fl_Double_Window(400,300,"Options");
  
  tabs = new Fl_Tabs(0, 0, 400, 300);
  
  int x, y, w, h;
  tabs->client_area( x, y, w, h, 25 );
  
  Fl_Group* bindingGroup = new Fl_Group( x, y, w, h, "Binding");
  {
    targetLabelStat = new Fl_Box(x + 100,y + 5, 75, 25,"Target: ");
    targetLabel = new Fl_Box(x + 140,y + 5, 200, 25,"");
    bindEnable = new Avtk::LightButton(x + 5, y + 5, 100, 25, "Bind Enable");
    
    Fl_Scroll* s = new Fl_Scroll( x + 5, y + 35, 400, 280 );
    bindings = new Avtk::Bindings( x + 5, y + 35, 400, 300 );
    s->end();
  }
  bindingGroup->end();

  Fl_Group* controllers = new Fl_Group( x, y, w, h, "Controllers");
  controllers->hide();
  {
    ctlrButton = new Avtk::Button(x + 5, y + 5, 100, 25, "Add Controller");
  }
  controllers->end();
  
  tabs->end();
  
  //ctlrButton->callback( selectLoadController );
  bindEnable->callback( writeBindEnable, this );
  
  window->end();
}

void OptionsWindow::setTarget(const char* t)
{
  if ( target )
    free (target);
  target = strdup(t);
  
  targetLabel->label( target );
  targetLabel->redraw();
  
  //LUPPP_NOTE("New Target %s\n", target );
}

void OptionsWindow::show()
{
  window->show();
}

void OptionsWindow::setBindEnable(bool e)
{
  bindEnable->value( e );
  setTarget("");
}

void OptionsWindow::addBinding( Binding* b )
{
  bindings->add( b );
}

