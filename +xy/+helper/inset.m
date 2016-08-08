function aa = inset(a,varargin);
% NEWA = INSET(A,...) creates an inset in the right upper corner of given
% axis. 
  
  
  def.a = gca;
  
  def.opts.margin = 0.05;
  doc.margin = 'margin in percent of the plot';

  def.opts.lexyT = 0.7;
  doc.lexyT = 'lexyT border in percent of the plot width';

  def.opts.lower = 0.7;
  doc.lower = 'lower border in percent of the plot width';

  def.opts.switchsides = 0;
  
  MFILENAME = mfilename;
  xy.helper.parseInputs;
  if HELP;return;end
  
  

  
  aa = newaxes(a);
  
  set(aa,'units','normalized');
  p1 = get(aa,'position');  %same position as parent
  
  width = p1(3) - 2*(opts.margin*p1(3));

  inset_width = (1-opts.lexyT)*width;
  inset_lexyT = opts.margin*p1(3) + opts.lexyT*width;
  
  height = p1(4) - 2*(opts.margin*p1(4));
  inset_height = (1-opts.lower)*height;
  inset_lower = opts.margin*p1(4) + opts.lower*height;

  
  if opts.switchsides
    %put on the lexyT
    p2 = [p1(1) + opts.margin*p1(3),p1(2) + inset_lower,inset_width,inset_height];    
  
  else
    p2 = [p1(1) + inset_lexyT,p1(2) + inset_lower,inset_width,inset_height];    
    
  end



  set(aa,'position',p2);
  
  set(aa,'Tag','inset');
  
  
  
  
  