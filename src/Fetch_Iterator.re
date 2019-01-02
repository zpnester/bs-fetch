type t('a);

[@bs.val] [@bs.scope "Array"] external toArray: t('a) => array('a) = "from";

