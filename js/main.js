(function($) {
    $.fn.enable_cropper = function(){
        setTimeout(function(){ //TODO: get rid of setTimeout function and use events if possible
            var container = $('#image-effect-form'),
                image = container.find('.image-preview img'),
                frame_left = container.find('input[name="data[frame_left]"]'),
                frame_top = container.find('input[name="data[frame_top]"]'),
                frame_right = container.find('input[name="data[frame_right]"]'),
                frame_bottom = container.find('input[name="data[frame_bottom]"]');
            if(frame_left.val() && frame_top.val() && frame_right.val() && frame_bottom.val()) {
                var data = {
                    left: parseFloat(frame_left.val()),
                    top: parseFloat(frame_top.val()),
                    width: parseFloat(frame_right.val()),
                    height: parseFloat(frame_bottom.val())
                };
                console.log(data);
            }
            image.cropper({
                zoomable: false,
                crop: function(e) {
                    var imageData = image.cropper('getImageData');
                    if (e.x && e.y && e.width && e.height) {
                        frame_left.val(e.x);
                        frame_top.val(e.y);
                        frame_right.val(imageData.naturalWidth - e.width - e.x);
                        frame_bottom.val(imageData.naturalHeight - e.height - e.y);
                    }
                },
                built: function(e) {
                    if (data) {
                        var canvasData = image.cropper('getCanvasData'),
                            imageData = image.cropper('getImageData'),
                            scaleFactor = canvasData.width / canvasData.naturalWidth;
                        data.width = imageData.width - (data.width + data.left) * scaleFactor; // TODO: fix bug when saving settings without moving crop frame
                        data.height = imageData.height - (data.height + data.top) * scaleFactor;
                        data.top = data.top * scaleFactor + image.cropper('getCanvasData').top;
                        data.left = data.left * scaleFactor + image.cropper('getCanvasData').left;
                        console.log(data);
                        image.cropper('setCropBoxData', data);
                    }
                }
            });
        },300);
    }
})(jQuery);