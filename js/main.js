(function($) {
    $.fn.enable_cropper = function(){
        setTimeout(function(){ //TODO: get rid of setTimeout function and use events if possible
            var container = $('#image-effect-form'),
                image = container.find('.image-preview img'),
                frame_x = container.find('input[name="data[frame_x]"]'),
                frame_y = container.find('input[name="data[frame_y]"]'),
                frame_width = container.find('input[name="data[frame_width]"]'),
                frame_height = container.find('input[name="data[frame_height]"]');

            if(frame_x.val() && frame_y.val() && frame_width.val() && frame_height.val()) {
                var data = {
                    left: parseFloat(frame_x.val()),
                    top: parseFloat(frame_y.val()),
                    width: parseFloat(frame_width.val()),
                    height: parseFloat(frame_height.val())
                };
            }
            image.cropper({
                zoomable: false,
                crop: function(e) {
                    frame_x.val(e.x);
                    frame_y.val(e.y);
                    frame_width.val(e.width);
                    frame_height.val(e.height);
                    console.log(e.x);
                    console.log(e.y);
                    console.log(e.width);
                    console.log(e.height);
                },
                built: function(e) {
                    if (data) {
                        canvasData = image.cropper('getCanvasData');
                        var scaleFactor = canvasData.width / canvasData.naturalWidth;
                        data.top = data.top * scaleFactor;
                        data.left = data.left * scaleFactor;
                        data.width = data.width * scaleFactor;
                        data.height = data.height * scaleFactor;
                        data.top = data.top + image.cropper('getCanvasData').top;
                        data.left = data.left + image.cropper('getCanvasData').left;
                        image.cropper('setCropBoxData', data);
                    }
                }
            });
        },300);
    }
})(jQuery);