var contentPane         = document.getElementById ('ContentPane');
var menuPanePlantUml    = document.getElementById ('PlantUml');
var menuPanePlantUmlPng = document.getElementById ('PlantUmlPng');
var menuPaneDotGraph    = document.getElementById ('DotGraph');
var menuPaneDotGraphPng = document.getElementById ('DotGraphPng')
var contentImage        = document.getElementById ('ContentImage');
var expandButton        = document.getElementById ('ExpandButton');
var contractButton      = document.getElementById ('ContractButton');
var currentImageWidth   = 100;

menuPanePlantUml.onclick = function ()
{
    var contentImage = document.getElementById ('ContentImage');
    var contentIFrame = document.getElementById ('ContentIFrame');

    if (null !== contentImage)
    {
	contentImage.style.display = 'NONE';
    }

    if (null === contentIFrame)
    {
        contentIFrame = document.createElement ('IFRAME');

	contentIFrame.setAttribute ('ID',          'ContentIFrame');
	contentIFrame.setAttribute ('WIDTH',       '100%');
	contentIFrame.setAttribute ('HEIGHT',      '100%');
	contentIFrame.setAttribute ('FRAMEBORDER', '0');

	contentPane.appendChild (contentIFrame);
    }

    contentIFrame.setAttribute ('SRC', '/Wave/Rest/ObjectModel/plantUml');
    contentIFrame.style.display = 'BLOCK';
}

menuPanePlantUmlPng.onclick = function ()
{
    var contentImage = document.getElementById ('ContentImage');
    var contentIFrame = document.getElementById ('ContentIFrame');

    if (null !== contentIFrame)
    {
        contentIFrame.style.display = 'NONE';
    }

    if (null === contentImage)
    {
        contentImage = document.createElement ('IMG');

	contentImage.setAttribute ('ID',     'ContentImage');

	contentPane.appendChild (contentImage);
    }

    contentImage.setAttribute ('SRC', '/Wave/Rest/ObjectModel/plantUml.png');
    contentImage.style.display = 'BLOCK';
    contentImage.setAttribute ('WIDTH',  '100%');
    contentImage.setAttribute ('HEIGHT', 'AUTO');
}

menuPaneDotGraph.onclick = function ()
{
    var contentImage = document.getElementById ('ContentImage');
    var contentIFrame = document.getElementById ('ContentIFrame');

    if (null !== contentImage)
    {
	contentImage.style.display = 'NONE';
    }

    if (null === contentIFrame)
    {
        contentIFrame = document.createElement ('IFRAME');

	contentIFrame.setAttribute ('ID',          'ContentIFrame');
	contentIFrame.setAttribute ('WIDTH',       '100%');
	contentIFrame.setAttribute ('HEIGHT',      '100%');
	contentIFrame.setAttribute ('FRAMEBORDER', '0');

	contentPane.appendChild (contentIFrame);
    }

    contentIFrame.setAttribute ('SRC', '/Wave/Rest/ObjectModel/dotGraph');
    contentIFrame.style.display = 'BLOCK';
}

menuPaneDotGraphPng.onclick = function ()
{
    var contentImage = document.getElementById ('ContentImage');
    var contentIFrame = document.getElementById ('ContentIFrame');

    if (null !== contentIFrame)
    {
        contentIFrame.style.display = 'NONE';
    }

    if (null === contentImage)
    {
        contentImage = document.createElement ('IMG');

	contentImage.setAttribute ('ID',     'ContentImage');

	contentPane.appendChild (contentImage);
    }

    contentImage.setAttribute ('SRC', '/Wave/Rest/ObjectModel/dotGraph.png');
    contentImage.style.display = 'BLOCK';
    contentImage.setAttribute ('WIDTH',  '100%');
    contentImage.setAttribute ('HEIGHT', 'AUTO');
}

contentImage.onclick = function ()
{
    var imageWidth = contentImage.getAttribute ('WIDTH');

    if ('AUTO' === imageWidth)
    {
        //contentImage.setAttribute ('WIDTH',  '100%');
    }
    else
    {
        //contentImage.setAttribute ('WIDTH',  'AUTO');
    }

    //contentImage.setAttribute ('HEIGHT', 'AUTO');
}

contentImage.onmouseup = function (event)
{
    var element = contentImage;

    var x = element.offsetLeft;
    var y = element.offsetTop;

    element = element.offsetParent;

    while (null != element)
    {
        x = parseInt (x) + parseInt (element.offsetLeft);
        y = parseInt (y) + parseInt (element.offsetTop);

	element = element.offsetParent;
    }

    window.scrollBy (parseInt (event.clientX) - (parseInt (document.body.clientWidth) / 2),  parseInt (event.clientY) - (parseInt (document.body.clientHeight) / 2));
}

contractButton.onclick = function ()
{
    if (currentImageWidth > 50)
    {
        currentImageWidth -= 10;
    }

    contentImage.setAttribute ('WIDTH', currentImageWidth + '%');
}

expandButton.onclick = function ()
{
    if (currentImageWidth < 300)
    {
        currentImageWidth += 10;
    }

    contentImage.setAttribute ('WIDTH', currentImageWidth + '%');
}

