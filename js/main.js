function enable_cropper(){ //TODO: find way to wrap it in jQuery
        console.log('enable cropper');
    setTimeout(function(){ //TODO: get rid of setTimeout function and use events if possible
        jQuery('.easy-frames-frame-image .image-preview img').cropper({
            zoomable: false,
            crop: function(e) {
                // Output the result data for cropping image.
                jQuery('input[name="data[frame_x]"]').val(e.x);
                jQuery('input[name="data[frame_y]"]').val(e.y);
                jQuery('input[name="data[frame_width]"]').val(e.width);
                jQuery('input[name="data[frame_height]"]').val(e.height);
                console.log(e.x);
                console.log(e.y);
                console.log(e.width);
                console.log(e.height);
                console.log(e.rotate);
                console.log(e.scaleX);
                console.log(e.scaleY);
            }
        });
    },300);
}
